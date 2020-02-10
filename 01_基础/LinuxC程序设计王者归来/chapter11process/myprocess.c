/***********************************************************
 * @Description : 
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2018/1/14 下午10:29
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <unistd.h>
#include "myprocess.h"

void createProcess() {
    pid_t pid, ppid, uid, euid, gid, egid;
    pid = getpid();
    ppid = getppid();
    uid = getuid();
    euid = geteuid();
    gid = getgid();
    egid = getegid();
    printf("进程id: %u\n",pid);
    printf("父进程id: %u\n",ppid);
    printf("用户id: %u\n",uid);
    printf("有效用户id: %u\n",euid);
    printf("组id: %u\n",pid);
    printf("有效组id: %u\n",pid);
}