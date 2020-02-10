
# stat函数使用

## 可以用`stat 文件名`来查看文件的详细信息

## stat函数的使用范例

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void){
    struct stat sbuf;
    int len = 1;
    int ret = 0;
    ret = stat("test", &sbuf);
    if(ret == -1){
        perror("stat error:");
        exit(1);
    }
    // 文件大小
    printf("file len = %d\n", (int)sbuf.st_size);
    // 文件类型,参考"man 2 stat"命令得到的文档
    switch(sbuf.st_mode & S_IFMT){
        case S_IFSOCK:
            printf("socket");
            break;
        case S_IFLNK:
            printf("symbolic link");
            break;
        case S_IFREG:
            printf("regular file");
            break;
        case S_IFBLK:
            printf("block device");
            break;
        case S_IFDIR:
            printf("directory");
            break;
        case S_IFCHR:
            printf("character device");
            break;
        case S_IFIFO:
            printf("FIFO");
            break;
        default:
            break;
    }
        
    return 0;
}
```
> stat()改成lstat()可以穿透符号链接，直接显示软链接实际指向的文件属性和信息

## stat函数的全面案例

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void){
    struct stat sb;
    int len = 1;
    int ret = 0;
    ret = stat("test", &sb);
    if(ret == -1){
        perror("stat error:");
        exit(1);
    }
   switch (sb.st_mode & S_IFMT) {
       case S_IFBLK:  printf("block device\n");            break;
       case S_IFCHR:  printf("character device\n");        break;
       case S_IFDIR:  printf("directory\n");               break;
       case S_IFIFO:  printf("FIFO/pipe\n");               break;
       case S_IFLNK:  printf("symlink\n");                 break;
       case S_IFREG:  printf("regular file\n");            break;
       case S_IFSOCK: printf("socket\n");                  break;
       default:       printf("unknown?\n");                break;
   }

   printf("I-node number:            %ld\n", (long) sb.st_ino);

   printf("Mode:                     %lo (octal)\n",
           (unsigned long) sb.st_mode);

   printf("Link count:               %ld\n", (long) sb.st_nlink);
   printf("Ownership:                UID=%ld   GID=%ld\n",
           (long) sb.st_uid, (long) sb.st_gid);

   printf("Preferred I/O block size: %ld bytes\n",
           (long) sb.st_blksize);
   printf("File size:                %lld bytes\n",
           (long long) sb.st_size);
   printf("Blocks allocated:         %lld\n",
           (long long) sb.st_blocks);

   printf("Last status change:       %s", ctime(&sb.st_ctime));
   printf("Last file access:         %s", ctime(&sb.st_atime));
   printf("Last file modification:   %s", ctime(&sb.st_mtime));
        
    return 0;
}
```
