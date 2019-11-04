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

/* alloc_mem.c

  Allocate blocks of memory, as specified by command-line arguments. This
  program is useful for small experiments with the 'memory' cgroup controller.
*/
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    size_t blockSize, totalMem;
    int sleepUsecs, numAllocs;
    int j, k;
    char *p;

    if (argc < 2)
        usageErr("%s <block-size> [sleep-usecs [num-allocs]]\n", argv[0]);

    blockSize = strtol(argv[1], NULL, 0);
    sleepUsecs = (argc > 2) ? atoi(argv[2]) : 0;
    numAllocs = (argc > 3) ? atoi(argv[3]) : -1;

    totalMem = 0;

    for (j = 0; (numAllocs == -1) || (j < numAllocs); j++) {
        p = malloc(blockSize);
        if (p == NULL)
            errExit("malloc %d", j);

        /* Make sure virtual memory is actually allocated by touching
           every page */

        for (k = 0; k < blockSize; k += 1024)
            p[k] = 0;

        totalMem += blockSize;
        printf("%4d: address = %p; total = 0x%zx (%zd MiB)\n",
                j, p, totalMem, totalMem / (1024 * 1024));

        /* If the user requested, slow things down by sleeping
           for some microseconds between each allocation */

        if (sleepUsecs != 0)
            usleep(sleepUsecs);
    }

    /* Pause, so that we hold onto allocated memory */

    printf("All memory allocated; pausing\n");
    pause();

    exit(EXIT_SUCCESS);
}
