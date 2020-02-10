# 13. opendir、readdir

+ `opendir`：打开目录，以便调用readdir读取目录项
+ `readdir`：读取目录里面的目录项

什么是目录项？
目录里面的数据，其实就是一条一条的目录项，每个目录项就是一个文件的基本信息，包含两个最重要的基本信息: 文件名和inode节点号
图：

## 13.1 opendir

### 13.1.1 函数原型

```c
#include <sys/types.h>
#include <dirent.h>

DIR *opendir(const char *name);
```

#### （1）功能：打开目录

不能使用open函数打开目录，只能使用opendir打开。

#### （2）参数name：需打开目录的路径名

#### （3）返回值

+ 调用成功：返回一个`DIR *`的指针，这个指针指向了被打开的目录，readdir通过这个指针就可以读取目录的目录项。
+ 调用失败：返回NULL, errno被设置。

### 13.1.2 代码演示

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

#define print_error(str) \
do{\
    fprintf(stderr, "File %s, Line %d, Function %s error\n",__FILE__, __LINE__, __func__);\
    perror(str);\
    exit(-1);\
}while(0);


int main(void)
{
    DIR *dirp = NULL;
    dirp = opendir("file.txt");
    if(NULL == dirp){
        print_error("opendir error");
    }
    
    return 0;
}
```

## 13.2 readdir

### 13.2.1 函数原型

```c
#include <dirent.h>
struct dirent *readdir(DIR *dirp);
```

#### （1）功能

读取目录里的目录项。
每调用一次，就读取出一条目录项。

#### （2）参数dirp：opendir打开目录时，得到的指针。

#### （3）返回值：调用成功，返回指针指向struct dirent结构体的指针。

man readdir能查看到这个结构体，这个结构体其实是定义在了<dirent.h>头文件中。

这个结构体就是用来存放一条目录项的，调用readdir读取到目录项后，会自动开辟一个struct dirent变量来存放目录项，然后将变量的指针返回，应用程序通过这个指针，就可以访问结构体中的目录项信息(文件基本信息)

```c
struct dirent
{
    ino_t           d_ino;        /* i节点编号 */ 重点
    off_t           d_off;        /* 地址偏移 */
    unsigned short  d_reclen;     /* 本条目录项的大小 */
    unsigned char   d_type;       /* 文件类型，不是所有系统都支持 */
    char            d_name[256];  /* 文件名字 */ 重点
};
```

返回NULL的话有如下两种情况：
+ 1）读到目录的末尾时，返回NULL
+ 2）函数调用失败时，也返回NULL, 不过errno被设置

怎么判断函数是否调用失败了呢
+ 如果`ernno==0`, 表示没有设置错误号，返回NULL是因为读到了文件的末尾  
+ 如果`errno!=0`, 表示是因为函数调用出错而返回的NULL  

#### （5）代码演示

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

#define print_error(str) \
do{\
    fprintf(stderr, "File %s, Line %d, Function %s error\n",__FILE__, __LINE__, __func__);\
    perror(str);\
    exit(-1);\
}while(0);


int main(void)
{
    // 1.打开当前文件夹
    DIR *dirp = NULL;
    dirp = opendir(".");
    if(NULL == dirp){
        print_error("opendir error");
    }
    
    // 2.循环读取当前文件夹下的文件
    while(1){
        struct dirent  *direntp = NULL;
        direntp = readdir(dirp);
        
        // 2.1 读文件出错
        if((NULL == direntp)&& (errno !=0)){
            print_error("readdir errnr");
        }
        
        // 2.2 说明到达了目录的尾部
        if((NULL == direntp)&& (errno == 0)) break;
        
        // 2.3 没到末尾就打印出当前所在条目的名字
        printf("inode id = %ld, file name = %s\n", direntp->d_ino, direntp->d_name);
    }
    
    return 0;
}
```

结果如下：

```shell
inode id = 2308408, file name = unmask_test
inode id = 2308426, file name = unmask_test.c
inode id = 2308411, file name = file.txt
inode id = 2308436, file name = getcwd_test
inode id = 2308435, file name = readlink_test
inode id = 2308432, file name = syslink_test.c
inode id = 2308425, file name = .
inode id = 2308444, file name = opendir
inode id = 2308373, file name = ..
inode id = 2308416, file name = truncate.c
inode id = 2308441, file name = opendir.c
inode id = 2308437, file name = readlink_test.c
inode id = 2308434, file name = syslink_test
inode id = 2308403, file name = getcwd_test.c
inode id = 2308440, file name = pfile
inode id = 2308430, file name = truncate
```
  
# 14. chmode、fchmod

## 14.1 函数原型

```c
#include <sys/stat.h>

int chmod(const char *pathname, mode_t mode);
int fchmod(int fd, mode_t mode);

```

+ （1）功能：修改文件权限，比如将权限指定为0664等。chmod命令就是调用这两个函数来实现的。
  + `chmod`：使用路径名操作
  + `fchmod`：使用文件描述符操作

+ （2）返回值
  + 成功返回0
  + 失败返回-1，errno被设置

# 14.2 代码演示

  ```c
  chmod("./file.txt", 0644);
  fchmod(fd, 0644);
  ```

