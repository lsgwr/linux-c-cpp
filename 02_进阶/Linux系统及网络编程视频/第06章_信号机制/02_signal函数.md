# 2. signal函数			

## 2.1 函数原型

```c
#include <signal.h>
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
```

### （1）功能：设置某个信号的处理方式。

处理方式可以被设置为忽略，捕获，默认。

进程的进程表（task_struct）中会有一个“信号处理方式登记表”，专门用于记录信号的处理方式，调用signal函数设置某个信号的处理方式时，会将信号的处理方式登记到该表中(连续设置多个信号会进行累加而不是覆盖)

每个进程拥有独立的task_struct结构体变量，因而每个进程的“信号处理方式登记表”都是独立的，所以每个进程对信号的处理方式自然也是独立的，互不干扰。

### （2）参数

+ 1）signum：信号编号
+ 2）handler：信号处理方式
  
  sighandler_t是被typedef后的类型，原类型 `void (*)(int)`，这是一个函数指针类型, `sighandler_t handler`也有直接写成`void (*handler)(int)`

  ```c
  sighandler_t signal(int signum, void (*handler)(int));
  ```

  + （a）忽略：SIG_IGN `ignore`
  + （b）默认：SIG_DFL `default`
  + （c）捕获：填写类型为`void (*)(int)`的捕获函数的地址，当信号发生时，会自动调用捕获函数来进行相应的处理  
      当然这个捕获函数需要我们自己来实现，捕获函数的int参数，用于接收信号编号  

      捕获函数也被称为信号处理函数。

      ```c
      void signal_fun1(int signo)
      {
        ...
      }

      void signal_fun2(int signo)
      {
        ...
      }

      int main(void)
      {
        signal(SIGINT, signal_fun1);
        signal(SIGSEGV, signal_fun2);

        return 0;
      }
      ```

      捕获函数什么时候被调用？  
      进程接收到信号时就调用，调用时会中断进程的正常运行，当调用完毕后再会返回进程的正常运行。

### （3）返回值

+ 成功：返回上一次的处理方式
+ 失败：返回SIG_ERR宏值，并且设置errno。

## 2.2 代码演示

+ 忽略

  ```c
  #include <stdio.h>
  #include <signal.h>

  int main(void)
  {
      signal(SIGINT, SIG_IGN); // 忽略SIGINT信号,这时候CTL+C就不管用了
      while(1);

      return 0;
  }
  ```

  执行上面的代码，按Ctrl+C是无效地，因为代码捕获并跳过了SIGINT信号
  
+ 捕获

  ```c
  #include <stdio.h>
  #include <signal.h>

  void catch_signal(int signo)
  {
      printf("信号的编号 = %d\n", signo);
  }

  int main(void)
  {
      signal(SIGINT, catch_signal);
      signal(SIGQUIT, catch_signal); // "Ctrl + \",signal多次调用就可以注册多个信号处理，累加而不是覆盖
      while(1);
      return 0;
  }
  ```

  运行后按Ctrl+C可以得到如下结果：

  ```shell
  ^C信号的编号 = 2
  ^C信号的编号 = 2
  ^\信号的编号 = 3
  ......
  ```

+ 返回值

  ```c
  #include <stdio.h>
  #include <signal.h>
  typedef void (*sighandler_t)(int);

  void catch_signal(int signo)
  {
      printf("信号的编号 = %d\n", signo);
  }

  int main(void)
  {
      sighandler_t ret = NULL;

      // signal执行成功返回地是上一次的信号捕获设置，比如下面代码输出地是default,注释掉第三个signal则结果是ignore
      ret = signal(SIGINT, SIG_IGN); // 忽略
      ret = signal(SIGINT, SIG_DFL); // 默认
      ret = signal(SIGINT, catch_signal); // 捕获

      if(ret == SIG_ERR){
          printf("signal fail\n");
      }else if(ret == SIG_IGN){
          printf("ignore\n");
      }else if(ret == SIG_DFL){
          printf("default\n");
      }else{
          printf("capture: %p\n", ret);
      }

      return 0;
  }
  ```

  输出为：

  ```shell
  default
  ```

### 2.2.1 例子1：重新设置SIGINT信号的处理方式

### 2.2.2 调用捕获函数的过程(类似单片机的中断)

#### （1）信号捕获的原理

当信号没有发生时，进程正常运行，当信号发生时，进程的正常运行会被中断，然后去处理信号，一看信号的处理方式是捕获，就会从“信号处理方式登记表”中将捕获函数的地址取出并执行捕获函数，捕获函数执行完毕后，恢复进程的正常运行。

不过当信号来时，如果当前有一条指令正在运行，会先等这条指令运行执行完毕后再去调用信号处理函数。				

不过如果捕获函数有调用exit或者_exit的话，进程会被终止，不过是正常终止。

如果信号处理函数有提前执行return的话，会提前返回到主线。

#### （2） 代码演示

将SIGINT的异常终止转为exit正常终止

这样的话，我们就可以调用“进程”终止处理函数，以及刷新“标准io”缓存了

```c
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
typedef void (*sighandler_t)(int);

void catch_signal(int signo)
{
    printf("信号的编号 = %d\n", signo);
    // 这里正常地退出可以把main和atexit注册的函数中的printf内容从缓存中刷新出来
    exit(-1); // 转为正常终止,注意_exit(-1);是不行地，
}

void process_exit_deal_fun(void)
{
    printf("process over");
    printf("save list to file");
}


int main(void)
{
    signal(SIGINT, catch_signal); // 接受Ctrl+C信号，捕获函数中进行正常退出
    atexit(process_exit_deal_fun); // 只有程序正常退出(exit)才能执行
    printf("hello");
    while(1);
    return 0;
}
```

按Ctrl+C可以得到

```shell
^Chello信号的编号 = 2
process oversave list to file
```

### 2.2.3 值得强调的地方

#### （1）信号被设置为SIG_DFL时，表示将处理方式设置为默认
  
  其实在不做任何处理方式设置的情况下，信号的处理方式就是系统设置的默认处理方式。

#### （2）信号被设置为SIG_IGN（忽略）时
  
进程将不会再接收到这个信号，这信号对进程没有任何影响。

#### （3）设置为捕获时，需要将handler设置为捕获函数的地址，类型为`void (*)(int)`

为了确保和捕获函数的类型统一，SIG_DFL、SIG_IGN和SIG_ERR宏的类型也必须是`void (*)(int)`

```c
#define SIG_DFL ((void (*)(int))0)
#define SIG_IGN ((void (*)(int))1)
#define SIG_ERR ((void (*)(int))-1)
```

验证这些值

这几个宏定义在了`<signal.h>`头文件中。

#### （4）除了SIGKILL这个信号外，其它所有的信号都可被忽略和捕获。

之所以不能忽略的原因，就是怕你把所有的信号都给忽略后，当你的程序跑飞后，除了重启机器外，你还就真没有办法终止跑飞的程序了
**所以Linux规定SIGKILL这个一定不能被忽略和捕获**，至少还有一个保底操作。