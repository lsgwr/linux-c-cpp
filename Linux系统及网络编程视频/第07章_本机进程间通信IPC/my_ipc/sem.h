#ifndef H_SEM_H
#define H_SEM_H
// 1.文件包含
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>

// 2.宏定义
#define SEM_FILE "./semfile"
#define PROJ_ID  'b'

#define print_error(str) \
do{\
    fprintf(stderr, "File %s, Line %d, Function %s error\n",__FILE__, __LINE__, __func__);\
    perror(str);\
    exit(-1);\
}while(0);

// 3.函数声明
extern int create_or_get_sem(int nsems);

#endif // H_SEM_H
