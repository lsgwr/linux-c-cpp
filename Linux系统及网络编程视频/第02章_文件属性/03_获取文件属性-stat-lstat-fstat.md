# 3、获取文件属性的函数，stat、lstat、fstat

这三个是兄弟函数，实现的功能相同，只是略微有区别，我们只要先把stat函数搞清楚了，lstat、fstat非常容易理解  

ls命令其实就是调用了这三个函数中的lstat来实现的，我们可以调用lstat函数来自己实现一个ls命令  

为什么要讲stat、lstat、fstat函数？
讲这三个函数，并不是真的想让你自己去实现一个ls命令，而是通过这三个函数的学习，深刻的理解文件各种属性，进而理解了“文件”是个什么东西  

## 3.1 stat

### 3.1.1、函数原型

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int stat(const char *path, struct stat *buf);
```

### 3.1.2、函数功能

功能就是获取文件的属性信息。

每个文件的属性信息，都是存在块设备上、该文件自己的inode节点空间中的。

调用stat函数时，文件系统通过stat给的path，到块设备上索引到该文件的inode节点空间，然后将里面的文件属性信息，读到应用程序的缓存中，如此就得到了文件的属性信息。

文件属性数据中转的过程：

```txt
应用缓存 <————— stat函数提供的内核缓存 <—————— 驱动程序的缓存 <—————— 块设备上的inode结点
```

### 3.1.3 返回值

调用成功，返回0，失败返回-1，errno被设置。

### 3.1.4 参数说明

```c
int stat(const char *path, struct stat *buf);
```

+ （1）`const char *path`：文件路径名

+ （2）`struct stat *buf`：应用缓存，用于存放读到的文件属性信息

    缓存的类型为struct stat，通过man stat，可以查看到struct stat结构体类型。

    ```c
    struct stat {
        dev_t     st_dev;        /* 块设备号（ID） */
        ino_t     st_ino;        /* inode结点号，文件属性信息所存inode节点的编号 */ 
        mode_t    st_mode;       /* 文件类型和文件权限*/  ls
        nlink_t   st_nlink;      /* 链接数 */             ls
        uid_t     st_uid;        /* 文件所属用户ID*/      ls
        gid_t     st_gid;        /* 文件所属组ID */       ls
        dev_t     st_rdev;       /* 字符设备ID */         
        off_t     st_size;       /* 文件大小 */
        blksize_t st_blksize;    /* 系统每次按块Io操作时，块的大小（一般是512或1024） */
        blkcnt_t  st_blocks;     /* 块的索引号 */

        /* windows下，文件的时间，同样也分为这三种 */
        time_t    st_atime;      /* 最后一次访问时间，read*/  ls
        time_t    st_mtime;      /* 最后一次修改时间，write */
        time_t    st_ctime;      /* 最后一次属性修改的时间，如权限被修改，文件所有者（属主）被修改 */
    };
    ```

    其中标记有ls的，表示这些属性，是我们ls查看时，会显示的内容

### 3.1.5 代码演示

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
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
    int ret = 0;
    struct stat state = {0}; // 务必初始化

    ret = stat(FILE_NAME, &state); // 取文件属性信息到结构体state中

    if(-1 == ret){
        print_error("stat fail");
    }

    printf("文件类型和文件权限 = %d\n", state.st_mode);
    printf("链接数 = %ld\n", state.st_nlink);
    printf("文件所属用户ID = %d\n", state.st_uid);
    printf("文件所属组ID = %d\n", state.st_gid);
    printf("文件大小 = %ld\n", state.st_size);
    printf("最后一次访问时间 = %ld\n", state.st_atime);
    printf("最后一次修改时间 = %ld\n", state.st_mtime);
    printf("最后一次属性修改的时间 = %ld\n", state.st_ctime);

    return 0;
}
```

结果为：

```shell
文件类型和文件权限 = 33188
链接数 = 1
文件所属用户ID = 0
文件所属组ID = 0
文件大小 = 18
最后一次访问时间 = 1553774875
最后一次修改时间 = 1553774882
最后一次属性修改的时间 = 1553774882
```

实现一个自己的ls命令（my_ls），将制定文件的属性信息打印出来  

为什么打印出来的都是数字？  
Linux都是以数字形式来管理属性信息的，我们需要自己把它翻译为更好理解英文字母(用if或者switch)  

我不知道使用什么格式来打印怎么办？  
不要紧，都是数字，不是`%d`就是`%u`、或者`%ld`等，先写一种，当编译器提示警告或者错误时，再根据提示的信息来改就行。

把程序改的更像ls命令：

+ （1）名字改为 my_ls
+ （2）ls可以跟参数，让我的程序也可以跟参数 代码演示：[stat.c](file_stat老师的代码/stat.c) 自己体会下就行，此处不自己再实现了

## 3.2 详细说一说struct stat结构体

```c
struct stat {
    dev_t     st_dev;        /* 块设备号 */
    ino_t     st_ino;        /* inode结点号，文件属性信息所存inode节点的编号 */ 
    mode_t    st_mode;       /* 文件类型和文件权限*/  ls
    nlink_t   st_nlink;      /* 链接数 */             ls
    uid_t     st_uid;        /* 文件所属用户ID*/      ls
    gid_t     st_gid;        /* 文件所属组ID */       ls
    dev_t     st_rdev;       /* 字符设备ID */
    off_t     st_size;       /* 文件大小 */
    blksize_t st_blksize;    /* 系统每次按块Io操作时，块的大小（一般是512或1024） */
    blkcnt_t  st_blocks;     /* 块的索引号 */

    time_t    st_atime;      /* 最后一次访问时间，read*/  ls
    time_t    st_mtime;      /* 最后一次修改时间，write */
    time_t    st_ctime;      /* 最后一次属性修改的时间，如权限被修改，文件所有者（属主）被修改 */
};
```

### 3.2.1 7类文件都有的属性

#### 7类文件都有的属性

```c
ino_t     st_ino;     /* inode结点号 */
mode_t    st_mode;    /* 文件类型和文件权限*/
nlink_t   st_nlink;   /* 链接数 */
uid_t     st_uid;     /* 文件所属用户ID*/
gid_t     st_gid;     /* 文件所属组ID */
off_t     st_size;    /* 文件大小 */
time_t    st_atime;   /* 最后一次访问时间，read*/
time_t    st_mtime;   /* 最后一次修改时间，write */
time_t    st_ctime;   /* 最后一次属性修改的时间，如权限被修改，文件所有者（属主）被修改 */
```

#### 专门给块设备文件用的

```c
dev_t     st_dev;      /* 块设备号 */
blksize_t st_blksize;  /* 系统每次按块Io操作时，块的大小（一般是512或1024） */
blkcnt_t  st_blocks;   /* 块的索引号 */
```

#### 专门给字符设备用的

```c
dev_t     st_rdev; /* 字符设备号（ID） */
```

### 3.2.3 详细的说一说ls的信息

```shell
st_mode       st_link   st_uid    st_gid    st_size    st_atime       文件名
-rwxrwxr-x      1        zxf       zxf       8944     Apr  2 20:05     a.out
```

其中不好理解的是st_mode、st_uid和st_gid，

#### （1）st_uid 和 st_gid

+ 1）`st_uid`
  + （a）`st_uid`是什么
       用户id（用户编号），编号是唯一的，例子中的编号1000代表的就是zxf这个用户
       在Linux下，是以编号形式来管理用户的，这有点像人名和身份证的关系
  + （c）文件属性中，为什么有st_uid
       表示文件的所属用户，好比现实生活中，文件上会标记该文件属于某某公司，道理其实是一样的。
  + （b）怎么把用户id变成zxf名字输出
        这个问题我们留到第4章《获取系统信息》时再来解决。

+ 2）`st_gid`

    多个用户可以在一起组成一个组，其中的某个用户会担任组长，该用户的用户id，就是整个组的组id

    这就好比张三、李四、王五组成了一个组，张三当组长，张三的身份证号也被作为了整个组的组id，张三的名字也被作为了整个组的组名

    **总结为：组长的用户名就是用户组名；组长的id就是用户组的id**  

    对于普通用户而言，自己一个人就是一组，组员和组长都是自己，所以一般情况下，ls显示文件的所属组时，就是所属用户亲自担任组长的那个组，而且组员就自己一人

    怎么把组id变成zxf名字输出？这个问题我们留到第4章《获取系统信息》时再来解决

#### （2）详解st_mode

+ 1）为什么要详解st_mode？

  介绍st_mode的目的是，希望通过st_mode的学习，深入理解文件权限这个东西。

  有关st_mode，关键是理解，而不是记忆，如果你把文件权限理解清楚了，以后凡是涉及与文件权限相关的知识点，对你来说都是so seay。

+ 2）ls显示的st_mode(比如`-rwxrwxr-x`)

  ```c
    st_mode    st_link    st_uid    st_gid    st_size    st_atime       文件名
  -rwxrwxr-x      1        zxf       zxf       8944     Apr 2 20:05     a.out
  ```

  | stat属性 | st_mode    | st_link | st_uid | st_gid | st_size | st_atime     | 文件名      |
  | ------ | ---------- | ------- | ------ | ------ | ------- | ------------ | -------- |
  | 含义     | 文件类型和文件权限  | 链接数     | 用户ID   | 组ID    | 文件大小    | 最后一次访问时间     | 文件名      |
  | 值举例    | -rwxrwxr-x | 1       | zxf    | st_gid | 8944    | Mar 27 03:52 | file.txt |

  + （a）`-` ：文件类型
  + （b）`rwxrwxr-x`：文件权限
    + 每三个为一组（rwx rwx r-x），分别为read(读)、write(写)、exe(执行)
      + 每组第一个：如果是-，表示不能读，如果是r，表示可以读
      + 每组第二个：如果是-，表示不能写，如果是w，表示可以写
      + 每组第三个：如果是-，表示不可以被cpu执行，如果是x，表示可以被执行

      如果是编译得到的可执行文件（里面所放的内容是机器指令），这个文件是可以被cpu执行的

    + 看看每一组
      + 第一组：代表的是**文件所属用户**，对该文件的操作权限. 例子：
      + 第二组：代表的是**文件所属组里面其它的组员用户**，对该文件的操作权限
      + 第三组：除了**所属用户、所属组以外**的，其它用户对该文件的操作权限。
      举例：在普通用户下修改root用户的文件。

    + 三组权限的大小关系
      正常情况下，所属用户的操作权限 >= 组员用户的操作权限 >= 其它不相干用户的操作权限 
      这就好比：你自己的私人物品：
      + 所属用户：你，你拥有最高操作权限
      + 所属组：你和你的家人就是一个组，你的家人作为组员，拥有仅次于你的操作权限
      + 外人：你家人以外的人，显然拥有最低操作权限，低到甚至是没有操作权限

+ 3）将数字形式的st_mode，打印为-rwxrwxr-x形式

  + （a）st_mode的本质  
      st_mode的本质就是一个数字，我们看到的rwx的形式，只是形态转换的结果。

  + （b）st_mode的组成  
        我们以二进制来分析st_mode，**以二进制表示时，st_mode有16位**，包含**三部分信息**：

        ```c
                                     文件权限
                               比如：(rwx rwx r-x)
                             __________/\_________
        文件类型   设置位     |                   |
        * * * *    * * *     * * *   * * *   * * *
        1 1        1                   1
        0 0        0                   0
        ```

      比如：例子中的st_mode为33200，对应的二进制为：1000 000 110 110 000

  + （c）文件类型
    + 12~15 bit用于表示文件类型(最高的4位)
    + 如何表示文件类型

      ```c
         八进制        二进制
      - 0100000（1000 000000000000）：代表普通文件
      - 0040000（0100 000000000000）：代表目录文件
      - 0060000（0110 000000000000）：代表块设备文件
      - 0020000（0011 000000000000）：代表字符设备文件
      - 0010000（0001 000000000000）：代表管道文件
      - 0140000（1100 000000000000）：代表套接字文件
      - 0120000（1010 000000000000）：代表符号链接文件
      ```

      为了方便使用，在Linux系统提供的stat.h头文件中，给以上数字定义了宏名。
      我怎么知道是定义在stat.h中的？man stat 查到的。

      ```c
      #define S_IFREG  0100000
      #define S_IFDIR  0040000
      #define S_IFBLK  0060000
      #define S_IFCHR  0020000
      #define S_IFIFO  0010000
      #define S_IFSOCK 0140000
      #define S_IFLNK  0120000
      ```

      我们可以直接使用宏名。

    + 如何取出12~15位的值，然后用于判断文件的类型
      + 使用c语言中的 & 操作即可实现
         我们使用屏蔽字0170000（1111000000000000）&st_mode，将0~13清零（屏蔽），留下的12~15就是我们要的文件类型。	
         系统给这个屏蔽字定义了一个宏名，即#define S_IFMT  0170000

      + 比如：例子中的st_mode为：33200
        33200是十进制，转成八进制为100660

        ```c
        0100660（1000 000 110 110 000）
                            &
        0170000（1111 000 000 000 000）屏蔽字
        0100000（1000 000 000 000 000）文件类型
        ```

        经过比对，0100000显然是属于普通文件。

    + 如何快速判断文件类型
      为了方便我们操作，系统在stat.h中定义了相应的带参宏，可以让我们快速的判断文件的类型。

        ```c
        #define S_ISLNK(st_mode)  (((st_mode) & S_IFMT) == S_IFLNK)
        #define S_ISREG(st_mode)  (((st_mode) & S_IFMT) == S_IFREG)
        #define S_ISDIR(st_mode)  (((st_mode) & S_IFMT) == S_IFDIR)
        #define S_ISCHR(st_mode)  (((st_mode) & S_IFMT) == S_IFCHR)
        #define S_ISBLK(st_mode)  (((st_mode) & S_IFMT) == S_IFBLK)
        #define S_ISFIFO(st_mode) (((st_mode) & S_IFMT) == S_IFIFO)
        #define S_ISSOCK(st_mode) (((st_mode) & S_IFMT) == S_IFSOCK)
        ```

      每一个带参宏，用于判断一种文件类型，判断时会把st_mode&S_IFMT，然后与对应的类型比对，如果比对结果为真，就表示是这种类型的文件，否则就不是。

    + 代码演示：将数字表示的文件类型，打印为-dslbcf来表示

      ```c
      if(S_ISLNK(sta.st_mode)) file_type = 'l';
      else if(S_ISREG(sta.st_mode)) file_type = '-';
      else if(S_ISDIR(sta.st_mode)) file_type = 'd';
      else if(S_ISCHR(sta.st_mode)) file_type = 'c';
      else if(S_ISBLK(sta.st_mode)) file_type = 'b';
      else if(S_ISFIFO(sta.st_mode)) file_type = 'p';
      else if(S_ISSOCK(sta.st_mode)) file_type = 's';
      ```

      详细见[stat.c](file_stat老师的代码/stat.c)

  + （d）文件权限

     ```c
                                  文件权限
                              (比如：rwx rwx r-x)
                            __________/\_________
      文件类型    设置位     |                   |
      * * * *    * * *      * * *   * * *   * * *
      1 1        1                   1
      0 0        0                   0
     ```

    + 0~8bit：文件权限

      > 一共16位，文件权限的位置如下

       ```shell
                              user    group   other
        * * * *    * * *      * * *   * * *   * * *
                              1 1 1   1 1 1   1 1 1
                              r w x   r w x   r w x
                              0 0 0   0 0 0   0 0 0
        - - -   - - -   - - -
       ```

      + 从st_mode中提取文件权限
        + 提取`用户(user)`对应的权限
            在stat.h中，定义了对应的屏蔽字。

            ```c
                                                   文 件 权 限
                                          **** *** *** *** ***
            #define S_IRUSR 00400：对应的是0000 000 100 000 000，提取用户读权限
            #define S_IWUSR 00200：对应的是0000 000 010 000 000，提取用户写权限
            #define S_IXUSR 00100：对应的是0000 000 001 000 000，提取用户可执行权限
            ```

            比如提取例子中的st_mode值(33200)中的用户权限，`stat.st_mode & 宏`

            ```c
            1000 000 110 110 000
                      &
            0000 000 100 000 000 S_IRUSR

            1000 000 110 110 000
                      &
            0000 000 010 000 000 S_IWUSR

            1000 000 110 110 000
                      &
            0000 000 001 000 000 S_IXUSR
            ```

          + 提取`组(group)`对应的权限

             ```c
             1000 000 110 110 000 st_mode
              #define S_IRGRP 00040 (0000 000 000 100 000)
              #define S_IWGRP 00020 (0000 000 000 010 000)
              #define S_IXGRP 00010 (0000 000 000 001 000)
             ```

          + 提取`其他用户(other)`对应的权限

             ```c
             1000 000 110 110 000 st_mode
              #define S_IROTH 00004 (0000 000 000 000 100)
              #define S_IWOTH 00002 (0000 000 000 000 010)
              #define S_IXOTH 00001 (0000 000 000 000 001)
             ```

          + 代码演示
            将数字表示的读写权限，表示为rwx所表示的权限

            ```c
            /* 打印文件权限 */
            char buf[10] = {0};
            char tmp_buf[] = "rwxrwxrwx";
            for(i=0; i<9; i++)
            {
              if(sta.st_mode & (1<<(8-i))) {
                buf[i] = tmp_buf[i]; // 1依次次向右移动与st_mode的~0位取真值，获取文件权限
              }else {
                buf[i] = '-';
              }
            }
            printf("%s", buf);
            ```

            完整代码如下：

            ```c
            #include <stdio.h>
            #include <stdlib.h>
            #include <sys/types.h>
            #include <sys/stat.h>
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
                int ret = 0;
                struct stat state = {0}; // 务必初始化

                ret = stat(FILE_NAME, &state); // 取文件属性信息到结构体state中

                if(-1 == ret){
                    print_error("stat fail");
                }

                printf("文件类型和文件权限 = %d\n", state.st_mode);
                printf("链接数 = %ld\n", state.st_nlink);
                printf("文件所属用户ID = %d\n", state.st_uid);
                printf("文件所属组ID = %d\n", state.st_gid);
                printf("文件大小 = %ld\n", state.st_size);
                printf("最后一次访问时间 = %ld\n", state.st_atime);
                printf("最后一次修改时间 = %ld\n", state.st_mtime);
                printf("最后一次属性修改的时间 = %ld\n", state.st_ctime);

                int i = 0;

                /* 打印文件权限 */
                char buf[10] = {0};
                char tmp_buf[] = "rwxrwxrwx";
                for(i=0; i<9; i++)
                {
                  if(state.st_mode & (1<<(8-i))) {
                    buf[i] = tmp_buf[i]; // 1依次次向右移动与st_mode的~0位取真值，获取文件权限
                  }else {
                    buf[i] = '-';
                  }
                }
                printf("%s", buf);

                return 0;
            }
            ```

+ 4）如何使用chmod命令修改文件权限(rwx)
  + （a）方法1：直接使用数字
    + 例1：`chmod 0777 file.txt`
      这个0777，在命令行时，代表八进制的0可以省略。
      + 第一个7：user对应的权限，111

        ```shell
                    user  group  other
          **** ***  ***   ***    ***
                    111
        ```

      + 第二个7：group对应的权限，111

        ```shell
                  user  group  other
        **** ***  ***   ***    ***
                        111
        ```

      + 第三个7：other对应的权限，111

        ```shell
                  user  group other
        **** ***  ***   ***    ***
                               111
        ```

      修改后，文件的权限变为了：rwxrwxrwx。

    + 例2：chmod 0664 file.txt

      0664的二进制为110 110 100

      ```shell
                user  group  other
      **** ***  ***   ***    ***
                110   110    100
      ```

      修改后，文件的权限变为了：`rw-rw-r--`, 对于存放文字编码的普通文件来说，不需要任何的执行权限。

    + open创建文件时所指定的原始权限

      ```c
      fd = open("./new_file.txt", O_RDWR|O_CREAT, 0664);
      ```

      使用open系统API创建新文件时，需要制定一个原始的权限，比如指定的是0664的话，就表示，创建出的文件的原始权限为rw-rw-r--。

  + （b）方法2：直接使用rwx来设置

    ```shell
    user  group  other
    **** ***  ***   ***    ***
    ```

    + 例子1：修改所有`(user+group+other)`权限

      ```shell
      chmod a=rw- file.txt
      ```

      表示所有的权限全部指定为rw-

    + 例子2：只修改某一组的权限

      ```shell
                user  group  other
      **** ***  ***   ***    ***
      ```

    + `chmod u=rw- file.txt`  只将文件所属用户对应的权限设置为`rw-`

    + `chmod g=r-- file.txt`  只将文件所属组对应的权限设置为`r--`

    + `chmod o=r-- file.txt` 只将其它用户对应的权限设置为`r--`

    + `chmod u=rwx,g=rw-,o=r-- file.txt` 一次性的对三个权限都做设置

    + 例子3：只修改组里面某一位的权限

      ```shell
                user  group  other
      **** ***  ***   ***    ***
      ```

      + `chmod u+x file.txt`: user加上可执行权限
      + `chmod u-x file.txt`：user去掉可执行权限
      + `chmod u+x,u+r file.txt`：user加上可执行和读权限
      + `chmod g+w file.txt`：group加上写权限
      + `chmod o+r file.txt`：other加上读权限
      + `chmod u+r,g+w,o+x file.txt`：user加上读权限;group加上写权限;other加上可执行权限

#### 5）st_mode中的设置位

```c
                               文件权限
                        （比如：rwx rwx r-x）
                       __________/\_________
文件类型    设置位      |                   |
* * * *    * * *       * * *   * * *   * * *
1 1        1                   1
0 0        0                   0
```

设置位用的很少，因此这里就不再介绍具体介绍。

## 3.3 lstat

### 3.3.1 功能

> 与stat几乎完全一样，都是从块设备上的inode节点空间中读取文件的属性信息。但是与stat唯一不同的是，`lstat会区分链接文件`。

+ （1）`stat`：当操作对象是链接文件时，stat获取的文件属性是`链接文件背后所指向的文件，而不是链接文件的`
+ （2）`lstat`：当操作对象是链接文件时，lstat直接显示的是`链接文件本身的文件属性`

## 3.3 fstat

### 3.3.1 函数原型

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int fstat(int fd, struct stat *buf);
```

### 3.3.2 功能

和stat一样，也是用于获取文件属性。

不过与stat不同的是，**fstat是使用文件描述符来操作的**  

`当你不知道文件路径名，但是你知道指向这个文件的描述符时，就可以使用fstat来操作`

### 3.3.3 代码演示

## 3.4 思考：ls命令调用的是stat、lstat、fstat中哪一个函数?lstat

调用的是lstat，因为当ls的是链接文件时，能够单独的讲链接文件自己的属性显示出来，而不是背后所指向文件的属性。

## 3.5 `r` `w` `x`的含义

+ (1) r：表示文件可以被读
+ (2) w：表示文件可以被写
+ (3) x：表示文件可以被执行
  + 1）x对于普通文件来说
      如果普通文件存放的只是文字编码，因为文字编码无法被cpu执行，所以普通文件的x没有太大意义，所以一般的普通文件的x权限一般都是`-`
      如果普通文件里面存放的是机器指令，机器指令是可以被cpu执行的，存放机器指令的文件就必须要有x权限，如果没有是无法执行的
      比如gcc编译得到的可执行文件，里面放的就是机器指令，该文件默认就有x，所以才能被执行，否者文件是无法执行的。举例：

  + 2）x对于目录的意义?
      我们发现目录都有x，显然目录里面放的并不是机器指令，是不能被执行的，那么x对于目录的意义何在呢？
      `对于目录的x来说，也被称为通过权限`，也就是说，如果你的目录没有x权限，你是无法通过这个目录的。举例：

      ```c
      open("/dev/input/sda.txt", ...);
      ```

      如果/dev/input/sda.txt路径中的某个目录没有x，就无法通过这个目录，最终找不到sda.txt文件，这个路径就是一个无用路径
      `不过正常情况下，除非你自己刻意把目录的x设为-，否则创建的目录默认都有x，不会出现无法通过的情况`

  + 3）x对于其它文件来说，意义不大

+ (4) chown命令
  + 1）功能：用于修改文件的属主
  + 2）修改所属用户 `chown 新的所属用户 文件`
  + 3）修改所属组 `chown :新的组 文件`
  + 4）同时修改 `chown 新的所属用户:新的组 文件`
