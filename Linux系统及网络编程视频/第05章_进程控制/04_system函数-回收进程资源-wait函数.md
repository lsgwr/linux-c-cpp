# 4. system函数

如果我们需要创建一个进子进程，让子进程运行另一个程序的话，可以自己fork、execve来实现，但是这样的操作很麻烦，所以就有了system这个库函数

**这函数封装了fork和execve函数，调用时会自动的创建子进程空间，并把新程序的代码加载到子进程空间中，然后运行起来**.  

虽然有system这函数，但是我们还是单独的介绍了fork和execve函数，因为希望通过这两个函数的介绍，让大家理解当有OS支持时，程序时如何运行起来的。

## 4.1 system函数原型

```c
#include <stdlib.h>
int system(const char *command);
```

+ （1）功能：创建子进程，并加载新程序到子进程空间，运行起来。
+ （2）参数：新程序的路径名
+ （3）代码演示

    ```c
    #include <stdio.h>
    #include <stdlib.h>

    int main(void)
    {
        system("ls")
        system("ls -al");
        // system("可执行文件的绝对路径");
        return 0;
    }
   
    ```

# 5. 回收进程资源

> 进程运行终止后，不管进程是正常终止还是异常终止的，必须回收进程所占用的资源。

## 5.1 为什么要回收进程的资源？

+ （1）程序代码在内存中动态运行起来后，才有了进程，进程既然结束了，就需要将代码占用的内存空间让出来（释放）。
+ （2）OS为了管理进程，为每个进程在内存中开辟了一个task_stuct结构体变量，进程结束了，那么这个结构体所占用的内存空间也需要被释放。
+ （3）等其它资源

## 5.2 由谁来回收进程资源

由父进程来回收，父进程运行结束时，会负责释放子进程资源。

## 5.3 僵尸进程和孤儿进程

### 5.3.1 僵尸进程

子进程终止了，但是父进程还活着，父进程在没有回收子进程资源之前，子进程就是僵尸进程。

为什么子进程会变成僵尸进程？
子进程已经终止不再运行，但是父进程还在运行，它没有释放子进程占用的资源，所以就变成了占着资源不拉屎僵尸进程就好比人死后不腐烂，身体占用的资源得不到回收是一样的，像这种情况就是所谓的僵尸

### 5.3.2 孤儿进程

没爹没妈的孩子就是孤儿，子进程活着，但是父进程终止了，子进程就是孤儿进程。

为了能够回收孤进程终止后的资源，孤儿进程会被托管给我们前面介绍的pid==1的init进程，每当被托管的子进程终止时，init会立即主动回收孤儿进程资源，回收资源的速度很快，所以孤儿进程没有变成僵尸进程的机会。

### 5.3.3 演示

#### （1）僵尸进程(父亲活着，儿子死了)

> 没了儿子的爸爸如同行尸走肉

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    pid_t ret = 0;
    ret = fork();
    if(ret > 0){
        // 父进程
        while(1);
    }else if(ret == 0){
        // 子进程
        
    }
    return 0;
}
```

执行后会一直卡在`while(1)`, 所以父进程会一直运行(Run-R), 子进程立马执行完进入僵尸(Zombie-Z)状态  

用`ps -al`命令(查看正在终端运行的进程)查看如下：

```shell
F S   UID    PID   PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
4 S     0      9      1  0  80   0 - 308404 ep_pol pts/1   00:03:25 node
0 S     0     49     48  0  80   0 -  4561 wait   pts/1    00:00:00 bash
0 S     0     91     90  0  80   0 -  4547 wait_w pts/3    00:00:00 bash
0 S     0   9152      9  0  80   0 - 308503 ep_pol pts/1   00:00:01 node
0 S     0   9512   9511  0  80   0 -  2384 wait   pts/2    00:00:00 bash
0 S     0   9515   9512  0  80   0 - 185013 ep_pol pts/2   00:00:00 node
0 S     0   9528   9515  0  80   0 -  2973 sigsus pts/2    00:00:00 gdbserver
0 S     0   9530   9528  0  80   0 -  1050 unix_s pts/2    00:00:00 fd_demo
0 S     0   9533   9515  0  80   0 - 14569 poll_s pts/2    00:00:07 gdb
0 S     0  10302      9  0  80   0 - 310941 ep_pol pts/1   00:00:01 node
0 S     0  13430      9  0  80   0 - 326761 ep_pol pts/1   00:00:01 node
0 S     0  13988      9  0  80   0 - 359466 -     pts/1    00:00:03 node
0 R     0  15239     49 99  80   0 -  1050 -      pts/1    00:00:15 zombie_orphan  # 15239 < 15240表明为父进程;R代表进程正在运行
1 Z     0  15240  15239  0  80   0 -     0 exit   pts/1    00:00:00 zombie_orphan <defunct> # 15240 > 15239 表明为子进程;Z代表进程僵尸进程(Zombie)
0 S     0  15245  15244  0  80   0 -  4547 wait   pts/11   00:00:00 bash
0 R     0  15264  15245  0  80   0 -  1787 -      pts/11   00:00:00 ps
```
第2列的R、S、Z等的含义如下：
+ `ps` 查看到的进程状态
+ `R` 正在运行
+ `S` 处于休眠状态
+ `Z` 僵尸进程，进程运行完了，等待被回收资源

#### （2）孤儿进程(父亲死了，儿子活着)

> 没有爸爸，就成孤儿了

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    pid_t ret = 0;
    ret = fork();
    if(ret > 0){
        // 父进程
       
    }else if(ret == 0){
        // 子进程一直活着不退出
         while(1);
    }
    return 0;
}
```

用`ps -al`命令(查看正在终端运行的进程)查看如下：

```shell
F S   UID    PID   PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
4 S     0      9      1  0  80   0 - 308660 ep_pol pts/1   00:03:26 node
0 S     0     49     48  0  80   0 -  4561 wait_w pts/1    00:00:00 bash
0 S     0     91     90  0  80   0 -  4547 wait_w pts/3    00:00:00 bash
0 S     0   9152      9  0  80   0 - 308503 ep_pol pts/1   00:00:01 node
0 S     0   9512   9511  0  80   0 -  2384 wait   pts/2    00:00:00 bash
0 S     0   9515   9512  0  80   0 - 185013 ep_pol pts/2   00:00:00 node
0 S     0   9528   9515  0  80   0 -  2973 sigsus pts/2    00:00:00 gdbserver
0 S     0   9530   9528  0  80   0 -  1050 unix_s pts/2    00:00:00 fd_demo
0 S     0   9533   9515  0  80   0 - 14569 poll_s pts/2    00:00:07 gdb
0 S     0  10302      9  0  80   0 - 310941 ep_pol pts/1   00:00:01 node
0 S     0  13430      9  0  80   0 - 326761 ep_pol pts/1   00:00:01 node
0 S     0  13988      9  0  80   0 - 361260 ep_pol pts/1   00:00:03 node
0 S     0  15245  15244  0  80   0 -  4547 wait   pts/11   00:00:00 bash
1 R     0  15285      1 99  80   0 -  1050 -      pts/1    00:04:01 zombie_orphan # 可以看到只有子进程在跑，父进程已经没了
0 R     0  15394  15245  0  80   0 -  1787 -      pts/11   00:00:00 ps
```

# 6. wait函数

作用：父进程调用这个函数的功能有两个，

+ （1）主动获取子进程的“进程终止状态”
+ （2）主动回收子进程终止后所占用的资源

wait函数，在实际开发中用的很少，但是我们这里还是要介绍这个函数，因为如果你理解了这个函数，你才能理解进程return/exit/_exit所返回的返回值，到底返回给了谁。

## 6.1 进程的终止

### 6.1.1 正常终止

+ （1）main调用return
+ （2）任意位置调用exit
+ （3）任意位置调用_exit

不管哪种方式来正常终止，最终都是通过_exit返回到OS内核的  

### 6.1.2 异常终止

如果是被某个信号终止的，就是异常终止  

+ （1）自杀：自己调用abort函数，自己给自己发一个SIGABRT信号将自己杀死  
+ （2）他杀：由别人发一个信号，将其杀死  

### 6.1.3 进程终止状态

#### （1）退出状态与“进程终止状态”

我们在上一章里面将return、exit、_exit的返回值称为“进程终止状态”，严格来说应该叫“退出状态”，

return（退出状态）、exit（退出状态）或_exit(退出状态) 

当退出状态被_exit函数交给OS内核，OS对其进行加工之后得到的才是“进程终止状态”，父进程调用wait函数便可以得到这个“进程终止状态”  

通过 `echo $?`可以查看最近程序的执行结果状态  

#### （2）OS是怎么加工的？

+ 1）正常终止

 ```shell
 进程终止状态 = 终止原因（正常终止）<< 8 | 退出状态的低8位
 ```

 不管return、exit、_exit返回的返回值有多大，只有低8位有效，所以如果返回值太大，只取低8位的值(大于256只能取低8位)

+ 2）异常终止

  ```shell
  进程终止状态 = 是否产生core文件位 | 终止原因（异常终止）<< 8 | 终止该进程的信号编号
  ```

#### （3）父进程调用wait函数，得到“进程终止状态”有什么用

父进程得到进程终止状态后，就可以判断子进程终止的原因是什么，如果是正常终止的，可以提取出返回值，如果是异常终止的，可以提取出异常终止进程的信号编号  

讲到这里大家就明白了，当有OS支持时，进程return、exit、_exit正常终止时，所返回的返回值(退出状态), 最终通过“进程终止状态”返回给了父进程  

这有什么用，比如，父进程可以根据子进程的终止状态来判断子进程的终止原因，返回值等等，以决定是否重新启动子进程，或则做一些其它的操作，不过一般来说，子进程的终止状态对父进程并没有太大意义   

## 6.2 父进程如何从内核获取子终止状态

> 父进程可以获取，也可以不获取，父进程可以根据自己的具体需要来定  

### 6.2.1 如何获取

+ （1）父进程调用wait等子进程结束，如果子进程没有结束的话，父进程调用wait时会一直休眠的等(或者说阻塞的等)  
+ （2）子进程终止返回内核，内核构建“进程终止状态”  
  如果，  
  + 1）子进程是调用return、exit、_exit正常终止的，将退出状态返回给内核后，内核会通过如下表达式构建“进程终止状态”
  
     ```shell
     进程终止状态 = 终止原因（正常终止）<< 8 | 退出状态的低8位
     ```

  + 2）子进程是被某个信号异常终止的，内核会使用如下表达式构建“进程终止状态”

      ```shell
      进程终止状态 = 是否产生core文件位 | 终止原因（异常终止）<< 8 | 终止该进程的信号编号
      ```

+ （3）内核向父进程发送SIGCHLD信号，通知父进程子进程结束了，你可以获取子进程的“进程终止状态”了  
    如果父进程没有调用wait函数的话，会忽略这个信号，表示不关心子进程的“进程终止状态”    
    如果父进程正在调用wait函数等带子进程的“进程终止状态”的话，wait会被SIGCHLD信号唤醒，并获取进"进程终止状态"  

一般情况下，父进程都不关心子进程的终止状态是什么，所以我们经常看到的情况是，不管子进程返回什么返回值，其实都无所谓，因为父进程不关心。
不过如果我们的程序是一个多进程的程序，而且父进程有获取子进程“终止状态”的需求，此时我们就可以使用wait函数来获取了。

### 6.2.2 wait函数原型

```c
#include <sys/types.h>
#include <sys/wait.h>
pid_t wait(int *status);
```

+ （1）功能：获取子进程的终止状态，主动释放子进程占用的资源
+ （2）参数：用于存放“进程终止状态”的缓存
+ （3）返回值：成功返回子进程的PID，失败返回-1，errno被设置。
+ （4）代码演示
  
  ```c
  // fork.c 调用子进程代码并通过wait获取子进程状态
  #include <stdio.h>
  #include <unistd.h>
  #include <sys/types.h>
  #include <sys/wait.h>

  int main(int argc, char **argv, char **environ)
  {
      pid_t ret = -1;
      ret = fork();

      if(ret > 0){
          // 父进程
          int status = 0; // 子进程执行状态
          wait(&status); // 获取子进程执行状态到status中
          printf("子进程退出状态为：%d\n", status);
      }else if(ret == 0){
          // 子进程
          execve("./new_process", argv, environ); // execve调用外部自定义子进程
      }
      return 0;
  }
  ```
  
  ```c
  // new_process.c，用于编译生成可执行文件然后给fork.c调用
  #include <stdio.h>

  int main(int argc, char **argv, char **environ)
  {

      printf("当前所在程序：new_process.c\n");
      int i = 0;

      printf("\n-----------命令行参数----------\n");

      for(i = 0; i < argc; i++){
          printf("%s\n", argv[i]);
      }

      printf("\n-----------环境变量----------\n");
      for(i = 0; NULL != environ[i]; i++){
          printf("%s\n", environ[i]);
      }

      return 0; // 这个返回码会被fork.c里面的主进程wait函数()获取到
  }
  ```
  
  结果如下：
  
  ```c
  当前所在程序：new_process.c

  -----------命令行参数----------
  /workspace/chapter05pid/exec/fork

  -----------环境变量----------
  HOSTNAME=6fb4b72f0c7c
  SHELL=/bin/sh
  TERM=xterm-256color
  ISOUTPUTPANE=1
  TMUX=/tmp/tmux-0/cloud91.9,47,318
  PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
  SUPERVISOR_GROUP_NAME=cloud9
  PWD=/workspace/chapter05pid/exec
  NODE_PATH=/usr/lib/nodejs:/usr/lib/node_modules:/usr/share/javascript
  TMUX_PANE=%318
  NODE_ENV=production
  SUPERVISOR_ENABLED=1
  SHLVL=1
  HOME=/root
  SUPERVISOR_PROCESS_NAME=cloud9
  SUPERVISOR_SERVER_URL=unix:///var/run/supervisor.sock
  BASE_PROC=/workspace
  CUSTOM=43
  _=/usr/bin/node
  子进程退出状态为：0 # fork.c中的父进程捕获子进程new_process的退出码
  ```

### 6.2.3 从进程终止状态中提取进程终止的原因、返回值或者信号编号

#### （1）进程状态中所包含的信息

+ 1）正常终止
   
   ```shell
   进程终止状态 = 终止原因（正常终止）<< 8 | 退出状态的低8位
   ```
   
+ 2）异常终止
   
   ```shell
   进程终止状态 = 是否产生core文件位 | 终止原因（异常终止）<< 8 | 终止该进程的信号编号
   ```

#### （2）如何提取里面的信息

系统提供了相应的带参宏，使用这个带参宏就可以从“进程终止状态”中提取出我们要的信息。

提取原理：相应屏蔽字&进程终止状态，屏蔽掉不需要的内容，留下的就是你要的信息。

哪里能查到这些带参宏，man查案wait的函数手册，即可看到。

+ 1）`WIFEXITED(status)`：提取出终止原因，判断是否是**正常终止**, Wait If Exited    
  + （a）如果表达式为真：表示进程是正常终止的  
      此时使用`WEXITSTATUS(status)`，就可以从里面提取出`return/exit/_exit`返回的“退出状态”。

  + （b）为假：不是正常终止的

+ 2）`WIFSIGNALED(status)`：提取出终止原因，判断是否是**被信号杀死的(异常终止)** Wait If Signaled  
  + （a）如果表达式为真：是异常终止的  
      此时使用`WTERMSIG(status)`, 就可以从里面提取出终止该进程的信号编号。

  + （b）为假：不是异常终止的

#### （3）代码演示

通过判断终止原因、返回值、信号编号，父进程可以决定是否重新运行子进程，不过99%的情况是，父进程不关心子进程是怎么终止的，它的返回值是什么。

有关wait不要去记忆，我们讲wait的主要目的是想告诉你，进程的返回值到底返回给了谁

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **environ)
{
    pid_t ret = -1;
    ret = fork();
    
    if(ret > 0){
        // 父进程
        int status = 0; // 子进程执行状态
        wait(&status); // 获取子进程执行状态到status中
        printf("子进程退出状态为：%d\n", status);
        if(WIFEXITED(status)){
            // 如果正常退出的话
            printf("exited: %d\n", WEXITSTATUS(status));
        }else if(WIFSIGNALED(status)){
            // 异常退出
            printf("killed by signal: %d\n", WTERMSIG(status));   
        }
    }else if(ret == 0){
        // 子进程
        execve("./new_process", argv, environ); // execve调用外部自定义子进程
    }
    return 0;
}
```

```c
// new_process.c，用于编译生成可执行文件然后给fork.c调用
#include <stdio.h>

int main(int argc, char **argv, char **environ)
{

    printf("当前所在程序：new_process.c\n");
    int i = 0;

    printf("\n-----------命令行参数----------\n");

    for(i = 0; i < argc; i++){
        printf("%s\n", argv[i]);
    }

    printf("\n-----------环境变量----------\n");
    for(i = 0; NULL != environ[i]; i++){
        printf("%s\n", environ[i]);
    }
    
    while(1); // 用于挂起子进程，方便用"kill -信号码 pid号"来干掉进程
    
    return 0;
}
```

执行 `kill -10 new_process的pid`(用`ps -al`查看)得到如下输出(异常退出，被`WIFSIGNALED`捕获)：

```shell
cc     fork.c   -o fork
当前所在程序：new_process.c

-----------命令行参数----------
/workspace/chapter05pid/exec/fork

-----------环境变量----------
HOSTNAME=6fb4b72f0c7c
SHELL=/bin/sh
TERM=xterm-256color
ISOUTPUTPANE=1
TMUX=/tmp/tmux-0/cloud91.9,47,322
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
SUPERVISOR_GROUP_NAME=cloud9
PWD=/workspace/chapter05pid/exec
NODE_PATH=/usr/lib/nodejs:/usr/lib/node_modules:/usr/share/javascript
TMUX_PANE=%322
NODE_ENV=production
SUPERVISOR_ENABLED=1
SHLVL=1
HOME=/root
SUPERVISOR_PROCESS_NAME=cloud9
SUPERVISOR_SERVER_URL=unix:///var/run/supervisor.sock
BASE_PROC=/workspace
CUSTOM=43
_=/usr/bin/node
子进程退出状态为：10 # fork.c中的父进程捕获子进程new_process的退出码
killed by signal: 10 # 异常退出，被WIFSIGNALED(status)捕获
```

注释掉new_process.c中的while(1)那行，结果如下(正常退出，被`WIFEXITED`捕获):

```shell
当前所在程序：new_process.c

-----------命令行参数----------
/workspace/chapter05pid/exec/fork

-----------环境变量----------
HOSTNAME=6fb4b72f0c7c
SHELL=/bin/sh
TERM=xterm-256color
ISOUTPUTPANE=1
TMUX=/tmp/tmux-0/cloud91.9,47,320
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
SUPERVISOR_GROUP_NAME=cloud9
PWD=/workspace/chapter05pid/exec
NODE_PATH=/usr/lib/nodejs:/usr/lib/node_modules:/usr/share/javascript
TMUX_PANE=%320
NODE_ENV=production
SUPERVISOR_ENABLED=1
SHLVL=1
HOME=/root
SUPERVISOR_PROCESS_NAME=cloud9
SUPERVISOR_SERVER_URL=unix:///var/run/supervisor.sock
BASE_PROC=/workspace
CUSTOM=43
_=/usr/bin/node
子进程退出状态为：0 # fork.c中的父进程捕获子进程new_process的退出码
exited: 0 # 正常退出，用WIFEXITED(status捕获地)
```


#### （4）wait的缺点

如果父进程fork创建出了好多子进程，wait只能获取最先终止的那个子进程的“终止”状态，其它的将无法获取，如果你想获取所有子进程终止状态，或者只想获取指定子进程的进程终止状态，需要使用wait的兄弟函数waitpid，它们的原理是相似的，
所以我们这里不再赘述，也不用大家掌握，理解了wait就已经非常到位了。
