#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PATH_LEN 256
//dir=/home/itcast/1110_linux    fcn=isfile

void fetchdir(const char *dir, void (*fcn)(char *))//该函数被调用,既已被判定为目录
{
    char name[PATH_LEN];
    struct dirent *sdp;
    DIR *dp;

    if ((dp = opendir(dir)) == NULL) {     //打开目录失败,如:没有x权限
        //perror("fetchdir can't open");
        fprintf(stderr, "fetchdir: can't open %s\n", dir);
        return;
    }

    //
    while ((sdp = readdir(dp)) != NULL) {
        if (strcmp(sdp->d_name, ".") == 0 || strcmp(sdp->d_name, "..") == 0) {    //防止出现无限递归
            continue; 
        }

        if (strlen(dir)+strlen(sdp->d_name)+2 > sizeof(name)) {
            fprintf(stderr, "fetchdir: name %s %s too long\n", dir, sdp->d_name);
        } else {
            sprintf(name, "%s/%s", dir, sdp->d_name);
            (*fcn)(name);                     //这是一个什么??  
        }
    }

    closedir(dp);
}

void isfile(char *name)          //处理目录/文件
{
    struct stat sbuf;

   if (stat(name, &sbuf) == -1) {   //文件名无效
        fprintf(stderr, "isfile: can't access %s\n", name);
        exit(1);
    }
    if ((sbuf.st_mode & S_IFMT) == S_IFDIR) {  //判定是否为目录
        fetchdir(name, isfile);                //回调函数,谁是回调函数呢?
    }

    printf("%8ld %s\n", sbuf.st_size, name);   //不是目录,则是普通文件,直接打印文件名
}
//./ls_R ~/1110_linux
int main(int argc, char *argv[])
{
    if (argc == 1) 
        isfile(".");
    else
        while (--argc > 0)          //可一次查询多个目录 
            isfile(*++argv);        //循环调用该函数处理各个命令行传入的目录

    return 0;
}
