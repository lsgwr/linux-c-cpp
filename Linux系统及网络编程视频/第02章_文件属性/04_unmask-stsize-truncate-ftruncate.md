# 4. umask函数

## 4.1 open函数创建新文件时的一个问题 		

open函数创建新的文件时，如果指定的是0777满级权限的话，实际创建文件权限为0775（rwxrwxr-x）

### （1）为什么不是满级权限

> 因为被文件权限掩码做了限制,文件掩码越大对文件权限设置的限制越大

```shell
  111 111 111  (0777)
           &
 ~000 000 010  (0002) 文件权限掩码
 (111 111 101)
  111 111 101  (0775：rwxrwxr-x)
```

限制其它用户的写权限，为什么限制? 防止其它用户修改你的文件。

如果确实有创建满级权限的需求的话，就必须将文件权限掩码002修改为0

#### （2）怎么将文件权限掩码改为0? 
 
> 使用umask即可。

## 4.1 函数原型和所需头文件

```c
#include <sys/types.h>
#include <sys/stat.h>

mode_t umask(mode_t mask);
```

### （1）功能：修改文件权限掩码

### （2）参数mask：新的文件权限掩码

### （3）返回值

+ umask不会调用失败。
+ 返回值是`旧的文件权限掩码`

## 4.2 函数举例

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FILE_NAME "file.txt"

#define print_error(str) \
do{\
    fprintf(stderr, "File %s, Line %d, Function %s error\n",__FILE__, __LINE__, __func__);\
    perror(str);\
    exit(-1);\
}while(0);


int main(void)
{
    int fd = -1;
    
    // 下面这3行可以把系统掩码的限制(系统本来有个值为18的掩码,不同机器掩码可能不一样)放开
    // 使得777设置的权限就是rwxrwxrwx; 注释掉这3行结果就是rwxr-xr-x
    mode_t ret = 0;
    ret = umask(0);
    printf("oldMask = %d\n", ret);
    
    fd = open(FILE_NAME, O_RDWR | O_CREAT, 0777);
    
    if(fd < 0){
        print_error("open fail");
    }
    return 0;
}
```

结果输出：

```shell
oldMask = 18
```

命令查看文件信息的前后回显如下：

```shell
root@6fb4b72f0c7c:/workspace/chapter03# ll -ah file.txt 
-rwxr-xr-x 1 root root 0 Mar 29 03:11 file.txt*
root@6fb4b72f0c7c:/workspace/chapter03# ll -ah file.txt 
-rwxrwxrwx 1 root root 0 Mar 29 03:12 file.txt*
root@6fb4b72f0c7c:/workspace/chapter03# ./
file.txt     unmask_test  
root@6fb4b72f0c7c:/workspace/chapter03# ./unmask_test 
oldMask = 18
root@6fb4b72f0c7c:/workspace/chapter03# 
```

## 4.3 每一个进程都有一个文件权限掩码

我的程序，修改只是当前进程的文件权限掩码，对其它进程的文件权限掩码无影响。后面讲守护进程的时候就会用到umask函数。


# 5. 文件长度st_size

我们前面学习struct stat结构体时，这个结构体中的st_size被用来存放文件长度，但是这一项只对普通文件、目录、以及符号连接文件有意义。

因为只有普通文件、目录、以及符号链接文件才有实际的数据，有数据才有文件长度。

其它的文件在块设备上只存储了文件属性，它们只是挂了一个文件名，以文件的形式进行管理而已，没有实际的数据，所以对于这些文件来说，文件大小是没有意义的。

## 6.2 符号链接文件的文件大小 

符号链接文件就是一个快捷键，背后指向了某个文件。

符号链接文件的数据，就是所指向文件的文件名，所以它的文件大小指的就是这个名字的字符个数。

```shell
pfile -> file.txt
```

## 7. 文件截断函数truncate、	ftruncate		

我们学习open时，可以指定了O_TRUNC后，文件里面有数据的话，会将打开的文件截短（清空）为0

这一小节我们将要学习一个文件截短的函数truncate，**它不仅能够将文件截为0，还可以把文件截短为任意长度**

截取的长度length超过文件大小会产生文件空洞

## 7.1 函数原型和所需头文件

```c
#include <unistd.h>
#include <sys/types.h>

int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);
```

## 7.2 函数功能

> 将文件长度截短为length所指定长度。

+ `truncate` : 利用文件路径名操作
+ `ftruncate`: 利用文件描述符操作。

## 7.3 函数返回值：

+ 成功返回0
+ 失败返回-1, errno被设置

## 7.4 测试用例

+ `truncate("./file.txt", 10);`
+ `ftruncate(fd, 5);`
