# 4、kill、raise、alarm、pause、abort函数

## 4.1 kill、raise

### 4.1.1 函数原型

```c
#include <sys/types.h>
#include <signal.h>
int kill(pid_t pid, int sig);
```

kill命令就是调用这个函数来实现。

```c
#include <signal.h>
int raise(int sig);
```

+ （1）功能
  + 1）kill：向PID所指向的进程发送指定的信号。
  + 2）raise：向当前进程发送指定信号。							

+ （2）返回值
  + 1）kill：成功返回0，失败返回-1，errno被设置。
  + 2）rasie：成功返回0，失败返回非0。

### 4.1.2 代码演示

raise函数用的比较少，不过当多个进程协同工作时，kill函数有时还是会用到的。比如向其它进程发送某信号，通知其某件事情发生了，其它进程收到这个信号后，就会调用信号处理函数进行相应的处理，以实现协同工作。

## 4.2 alarm、pause

### 4.2.1 函数原型

```c
#include <unistd.h>
unsigned int alarm(unsigned int seconds);
int pause(void);
```

+ （1）功能
  + 1）alarm
    设置一个定时时间，当所设置的时间到后，内核会向调用alarm的进程发送SIGALRM信号。SIGALRM的默认处理方式是终止。

  + 2）pause函数
    调用该函数的进程会永久挂起（阻塞或者休眠），直至被信号（任意一个信号）唤醒为止。

+ （2）返回值
  + 1）alarm：返回上一次调用alarm时所设置时间的剩余值  
    如果之前没有调用过alarm，又或者之前调用alarm所设置的时间早就到了，那么返回的剩余值就是0

  + 2）pause：
    只要一直处于休眠状态，表示pause函数一直是调用成功的  
    当被信号唤醒后会返回-1，表示失败了，errno的错误号被设置EINTR（表示函数被信号中断）  

### 4.2.2 代码演示

alarm函数用的不多，pause在实际开发中也用的不多，不过在开发中往往会使用pause()函数来帮助调试，

比如我想让程序运行到某位置时就停下，然后分析程序的打印数据，此时就是可以关键位置使用pause函数将程序休眠(停下). 不想继续休眠时使用信号唤醒即可。	

## 4.3 abort函数	

我们前面的课程介绍过，这个函数也被称为叫自杀函数，之所以称为自杀函数，是因为调用该函数时，会向当前进程发一个SIGABRT信号，这个信号的默认处理方式是终止，因此如果不忽略和捕获的话，会将当前进程终止掉。
