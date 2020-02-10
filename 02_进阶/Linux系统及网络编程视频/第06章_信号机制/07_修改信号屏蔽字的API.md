# 7. 修改信号屏蔽字的API

## 7.1 修改的原理

### （1）定义一个64位的与屏蔽字类似的变量

### （2）将该变量设置为要的值

将某信号对应的位设置为0或者为1。

### （3）使用这个变量中的值来修改屏蔽字

修改方法有三种，当然以下这三种修改方法，我们并不需要自己亲自操作，只需要调用相应的API，API就会自动的实现。

+ 1）第一种：完全的替换
  使用变量的值去完全替换掉屏蔽字
  比如：
  
  ```shell
  屏蔽字 = 变量（1111111...11111）
  ```

  屏蔽所有信号，当然里面的SIGKILL和SIGSTOP信号是不能被屏蔽，就算在屏蔽字中它们对应的位设置为了1，也不会起到屏蔽的作用。

+ 2）第二种：使用|操作，将对应的位设置为1，只屏蔽某个或者某两个信号
  屏蔽字 = 屏蔽字 | 变量

  比如：
  
  ```shell
  屏蔽字 = 屏蔽字 | 0000...10
  ```

  将编号为2（SIGINT）的信号，在屏蔽字中对应的位设置为1，屏蔽字中其它的位不变

+ 3）第三种：使用位&操作，将对应的位清0，打开信号
  
  ```shell
  屏蔽字 = 屏蔽字 & (~变量)
  ```

  比如：
  
  ```shell
  屏蔽字 = 屏蔽字 & (~0000...10)
  屏蔽字 = 屏蔽字 & 1111...01,
  ```

  将编号为2（SIGINT）的信号，在屏蔽字中对应的位清0，其它位不变。

## 7.2 设置变量的API	

### 7.2.1 函数原型

```c
#include <signal.h>

int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int signum);
int sigdelset(sigset_t *set, int signum);
```

set就是我们前面说的变量，至于变量名也可以定义为其它的名字，不一定非要叫set。

+ （1）功能：设置变量的值
  + 1）**sigemptyset**：将变量set的64位全部设置为0
  + 2）**sigfillset**：将变量set的64位全部设置为1
  + 3）**sigaddset**：将变量set中，signum（信号编号）对应的那一位设置为1，其它为不变
  + 4）**sigdelset**：将变量set的signum（信号编号）对应的那一位设置为0，其它位不变


+ （2）返回值
  调用成功返回0，失败返回-1，并且errno被设置。

### 7.2.2 代码演示

后面再演示。

## 7.3 使用变量修改屏蔽字的API

### 7.3.1 函数原型

```c
#include <signal.h>
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
```

+ （1）功能：使用设置好的变量set去修改信号屏蔽字(经过7.2.1几个函数修改好的set变量)  
+ （2）参数  
  + 1）**how**：修改方式，前面说过有三种修改方式。
    + （a）**SIG_BLOCK**：屏蔽某个信号
        
        ```shell
        屏蔽字=屏蔽字 | set
        ```

    + （b）**SIG_UNBLOCK**：打开某个信号（不要屏蔽），实际就是对屏蔽字的某位进行清0操作  
      
      ```shell
      屏蔽字=屏蔽字&(~set)
      ```

    + （c）**SIG_SETMASK**：直接使用set的值替换掉屏蔽字

  + 2）**set**：set的地址  

  + 3）**oldset**：保存修改之前屏蔽字的值  
    如果写为NULL的话，就表示不保存

+ （3）返回值：函数调用成功返回0，失败返回-1。

### 7.3.3 代码演示 参考 [signal_mask.c](signal/signal_mask.c) 

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_func(int signo)
{
    sigset_t set;
    sigset_t oldset;
    sigemptyset(&set); // 将变量set的64位全部设置为0
    sigaddset(&set, SIGINT); // 将变量set中SIGINT对应的那一位设置为1，其它为不变
    sigprocmask(SIG_UNBLOCK, &set, &oldset); // 第一个参数表示对屏蔽字的某位进行清0操作;最后的参数表示保存旧的set值,不保存用NULL

    printf("hello\n");
    sleep(3); // 信号处理过程中信号屏蔽字一直为1，这个期间发SIGINT信号不会响应
    printf("world\n"); // 结果就是不管按下多少次Ctrl+C都能及时响应，因为每次信号处理都有把SIGINT信号清零恢复
}

int main(int argc, char **argv, char **environ)
{
    pid_t ret = 0;    
    signal(SIGINT, signal_func);
    
    while(1);
    return 0;
}
```

结果如下，不管按下多少次Ctrl+C都能及时响应，因为每次信号处理都有把SIGINT信号清零恢复

```shell
^Chello
^Chello
^Chello
^Chello
^Chello
^Chello
world
world
world
world
world
world
```

### 7.3.4 sigaction函数			
sigaction函数相当于是signal函数的复杂版，不过这个函数在平时用的非常少，因此我们这里不做详细讲解，了解有以下即可。
