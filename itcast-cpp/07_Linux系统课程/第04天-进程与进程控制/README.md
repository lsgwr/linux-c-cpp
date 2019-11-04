# 进程与进程控制

## 父子进程通信

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void sys_err(const char *str){
    perror(str);
    exit(1);
}

int main(void){
    int fd[2];
    int ret;
    pid_t pid;
    // 写入端需要写入的数据
    char *str = "hello pipe\n";
    // 读取端需要读取的缓冲区
    char buf[1024];

    // 设置进程读写管道
    ret = pipe(fd);
    if(ret == -1){
        sys_err("pipe error");
    }
    
    
    // 创建子进程
    pid = fork();
    if(pid == -1){
        sys_err("fork error");
    }else if(pid > 0){
        // 父进程，关闭读端
        close(fd[0]);
        // 向管道写数据
        write(fd[1], str, strlen(str));
        // 回收子进程
        wait(NULL);
        // 关闭写通道
        close(fd[1]);
    }else if(pid == 0){
        // 说明是子进程，关闭写端
        close(fd[1]);
        // 从读端读取数据
        ret = read(fd[0], buf, sizeof(buf));
        // 把buf的内容写到屏幕上
        write(STDOUT_FILENO, buf, ret);
        close(fd[0]);
    }
    return 0;
}
```
