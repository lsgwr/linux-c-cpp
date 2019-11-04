/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2018.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Supplementary program for Chapter Z */

/* ns_capable.c

   Test whether a process (identified by PID) might (subject to LSM checks)
   have capabilities in a namespace (identified by a /proc/PID/ns/xxx file).

   Usage: ./ns_capable <pid> <namespace-file>
*/
#define _GNU_SOURCE
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <limits.h>
#include <sys/capability.h>

#ifndef NS_GET_USERNS
#define NSIO    0xb7
#define NS_GET_USERNS           _IO(NSIO, 0x1)
#define NS_GET_PARENT           _IO(NSIO, 0x2)
#define NS_GET_NSTYPE           _IO(NSIO, 0x3)
#define NS_GET_OWNER_UID        _IO(NSIO, 0x4)
#endif

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)

#define fatal(msg)      do { fprintf(stderr, "%s\n", msg); \
                             exit(EXIT_FAILURE); } while (0)

/* Display capabilities of process with specified PID */

static void
display_process_capabilities(pid_t pid)
{
    cap_t caps;
    char *cap_string;

    caps = cap_get_pid(pid);
    if (caps == NULL)
        errExit("cap_get_proc");

    cap_string = cap_to_text(caps, NULL);
    if (cap_string == NULL)
        errExit("cap_to_text");

    printf("Capabilities: %s\n", cap_string);

    cap_free(caps);
    cap_free(cap_string);
}

/* Obtain the effective UID of the process 'pid' by
   scanning its /proc/PID/file */

static uid_t
euid_of_process(pid_t pid)
{
    char path[PATH_MAX];
    char line[1024];
    int uid;
    FILE *fp;

    snprintf(path, sizeof(path), "/proc/%ld/status", (long) pid);

    fp = fopen(path, "r");
    if (fp == NULL)
        errExit("fopen-/proc/PID/status");

    for (;;) {
        if (fgets(line, sizeof(line), fp) == NULL) {

            /* We reached EOF without finding "Uid:" record (should never
               happen) */

            fprintf(stderr, "Failure scanning %s\n", path);
            exit(EXIT_FAILURE);
        }

        if (strstr(line, "Uid:") == line) {
            sscanf(line, "Uid: %*d %d %*d %*d", &uid);
            fclose(fp);
            return uid;
        }
    }
}

/* Return true if two file descriptors refer to the same namespace,
   otherwise false */

static int
ns_equal(int nsfd1, int nsfd2)
{
    struct stat sb1, sb2;

    if (fstat(nsfd1, &sb1) == -1)
        errExit("fstat-nsfd1");
    if (fstat(nsfd2, &sb2) == -1)
        errExit("fstat-nsfd2");

    /* Namespaces are equal if *both* the device ID and the inode number
       in the 'stat' records match */

    return sb1.st_dev == sb2.st_dev && sb1.st_ino == sb2.st_ino;
}

/* Return the type of the namespace referred to by 'ns_fd' */

static int
ns_type(int ns_fd)
{
    int nstype = ioctl(ns_fd, NS_GET_NSTYPE);
    if (nstype == -1)
        errExit("ioctl-NS_GET_NSTYPE");

    return nstype;
}

/* Return a file descriptor for the user namespace that owns
   the namespace referred to by 'ns_fd' */

static int
owning_userns_of(int ns_fd)
{
    int userns_fd = ioctl(ns_fd, NS_GET_USERNS);
    if (userns_fd == -1)
        errExit("ioctl-NS_GET_USERNS");

    return userns_fd;
}

/* Return the UID of the creator of the namespace referred to by 'userns_fd' */

static int
uid_of_userns_owner(int userns_fd)
{
    uid_t owner_uid;

    if (ioctl(userns_fd, NS_GET_OWNER_UID, &owner_uid) == -1) {
        perror("ioctl-NS_GET_OWNER_UID");
        exit(EXIT_FAILURE);
    }

    return owner_uid;
}

/* Determine whether 'pid_userns_fd' is in an ancestor user namespace
   of the user namespace referred to by 'target_userns_fd'.

   Returns: -1 if 'pid_userns_fd' is not in an ancestor user namespace;
   otherwise, if 'pid_userns_fd' is in an ancestor user namespace, then a
   file descriptor that refers to the user namespace that is the immediate
   descendant of 'pid_userns_fd' in the chain of user namespaces from
   'pid_userns_fd' to 'target_userns_fd'. */

static int
search_ancestors(int target_userns_fd, int pid_userns_fd)
{
    int parent_userns_fd, desc_userns_fd;

    desc_userns_fd = target_userns_fd;

    for (;;) {
        parent_userns_fd = ioctl(desc_userns_fd, NS_GET_PARENT);

        if (parent_userns_fd == -1) {

            /* The error here should be EPERM, meaning no parent of this
               user namespace (because it is the initial namespace). Any
               other error is unexpected, and we terminate. */

            if (errno != EPERM)
                errExit("ioctl-NS_GET_PARENT");

            return -1;
        }

        /* If 'parent_userns_fd' and 'pid_userns_fd' are the same namespace,
           then the PID is in an ancestor namespace, and we need traverse
           no further in the series of user namespace ancestors */

        if (ns_equal(parent_userns_fd, pid_userns_fd)) {
            close(parent_userns_fd);    /* No longer need this FD */
            return desc_userns_fd;
        }

        /* Otherwise, check the next ancestor user namespace */

        int f = desc_userns_fd;
        desc_userns_fd = parent_userns_fd;
        close(f);
    }
}

int
main(int argc, char *argv[])
{
    int ns_fd, target_userns_fd, pid_userns_fd;
    int desc_userns_fd;
    char *pid_str;
    pid_t pid;
    char path[PATH_MAX];

    if (argc != 3) {
        fprintf(stderr, "Usage: %s PID ns-file\n", argv[0]);
        fprintf(stderr, "\t'ns-file' is a /proc/PID/ns/xxxx file\n");
        exit(EXIT_FAILURE);
    }

    pid_str = argv[1];
    pid = atoi(pid_str);

    ns_fd = open(argv[2], O_RDONLY);
    if (ns_fd == -1)
        errExit("open-ns-file");

    /* Get the relevant user namespace FD, which is 'ns_fd' if 'ns_fd' refers
       to a user namespace, otherwise the user namespace that owns 'ns_fd' */

    if (ns_type(ns_fd) == CLONE_NEWUSER) {
        target_userns_fd = ns_fd;
    } else {
        target_userns_fd = owning_userns_of(ns_fd);
        close(ns_fd);           /* No longer need this FD */
    }

    /* Obtain a file descriptor for the user namespace of the PID */

    snprintf(path, sizeof(path), "/proc/%s/ns/user", pid_str);

    pid_userns_fd = open(path, O_RDONLY);
    if (pid_userns_fd == -1)
        errExit("open-PID");

    /* If the PID is in the target user namespace, then it has
       whatever capabilities are in its sets. */

    if (ns_equal(pid_userns_fd, target_userns_fd)) {
        printf("PID %s is in the target namespace\n", pid_str);
        printf("Subject to LSM checks, it has the following capabilities\n");

        display_process_capabilities(pid);

        exit(EXIT_SUCCESS);
    }

    /* Otherwise, we need to walk through the ancestors of the target
       user namespace to see if PID is in an ancestor user namespace */

    desc_userns_fd = search_ancestors(target_userns_fd, pid_userns_fd);

    if (desc_userns_fd == -1) {

        /* If the return from search_ancestors() is -1, then PID was not in
           an ancestor user namespaces of 'target_userns_fd'. */

        printf("PID %s is not in an ancestor namespace\n", pid_str);
        printf("It has no capabilities in the target namespace\n");
        exit(EXIT_SUCCESS);
    }

    /* At this point, we found that PID is in a user namespace that is an
       ancestor of the target user namespace, and 'desc_userns_fd' refers
       to the immediate descendant of PID's user namespace in the chain of
       user namespaces from the user namespace of PID to the target user
       namespace. If the effective UID of PID matches the owner UID of the
       descendant user namespace, then PID has all capabilities in the
       descendant namespace(s); otherwise, it just has the capabilities that
       are in its sets. */

    printf("PID %s is in an ancestor namespace\n", pid_str);

    if (uid_of_userns_owner(desc_userns_fd) == euid_of_process(pid)) {
        printf("And its effective UID matches the owner "
                "of the immediate child user namespace\n"
                "of that namespace\n");
        printf("Subject to LSM checks, it has all capabilities in "
                "that namespace!\n");
    } else {
        printf("But its effective UID does not match the owner "
                "of the immediate child user namespace\n"
                "of that namespace\n");
        printf("Subject to LSM checks, it has the following "
                "capabilities\n");
        display_process_capabilities(pid);
    }

    close(desc_userns_fd);

    exit(EXIT_SUCCESS);
}
