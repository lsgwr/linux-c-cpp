# 文件操作常用函数

## access:获取文件的权限

```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if(access(argv[1], R_OK)){
        // 文件是否可读.此外还可以用W_OK(写权限)、X_OK(执行权限)、F_OK(文件是否存在)
        perror("access error");
        exit(1);
    }
    printf("able to read!\n");
    return 0;
}
```

## truncate:把文件截取到指定大小

```c
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
   int fd = open(argv[1], O_RDWR|O_CREAT, 0644);
   // 用了truncate就不需要额外触发IO操作了，所以第9行代码和10、11两行代码等效
   truncate(argv[1], 100);
//   lseek(fd, 99, SEEK_SET);
//   write(fd, "\0", 1);
   close(fd);
}
```

## link：创建硬链接

```c
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
   int fd = open(argv[1], O_RDWR|O_CREAT, 0644);
   // 创建硬链接(实现ln命令),参数1：oldpath,参数2: newpath
   int ret = link(argv[1], argv[2]);
   if(ret == -1){
       perror("link error");
       exit(1);
   }
   close(fd);
}
```

## unlink: 删除硬链接

```c
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
   int fd = open(argv[1], O_RDWR|O_CREAT, 0644);
   // 删除硬链接(实现ln命令),参数：newpath
   int ret = unlink(argv[1]);
   if(ret == -1){
       perror("unlink error");
       exit(1);
   }
   close(fd);
}
```
