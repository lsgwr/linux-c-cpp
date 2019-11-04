
# 目录操作函数

## getcwd:获取当前目录 chdir:切换当前目录

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    char buf[1024];
    char *path;
    // 获取当前目录
    path = getcwd(buf, sizeof(buf));
    printf("current path is %s\n", path);
    // 切换当前目录
    chdir("../");
    path = getcwd(buf, sizeof(buf));
    printf("current path is %s\n", path);
    return 0;
}
```


## opendir:打开目录 readdir:读取目录 closedir:关闭目录 下面的代码是读取指定目录下的所有文件(夹)

```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(void){
    DIR *dir;
    // 打开目录
    dir = opendir("/workspace");
    if(dir == NULL){
        perror("opendir() error");
        exit(1);
    }
    printf("open directory successfully!\n");
    
    // 读目录
    struct dirent *dirp;
    while((dirp = readdir(dir)) != NULL){
        printf("%s\t", dirp->d_name);
    }
    printf("\n");
    
    // 关闭目录
    closedir(dir);
    return 0;
}
```

## 应用：递归获取当前目录所有的文件和文件夹及其大小

```c
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
```
