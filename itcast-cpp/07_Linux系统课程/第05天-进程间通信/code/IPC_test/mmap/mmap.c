#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>

void sys_err(char *str)
{
    perror(str);
    exit(1);
}

int main(void)
{
    char *mem;
    int len = 0;

    int fd = open("hello678", O_RDWR|O_CREAT|O_TRUNC, 0644);
    if (fd < 0)
        sys_err("open error");
    len = lseek(fd, 3, SEEK_SET);   //获取文件大小,根据文件大小创建映射区
    write(fd, "\0", 1);              //实质性完成文件拓展
    len = lseek(fd, 0, SEEK_END);
    
    printf("The length of file = %d\n", len);

    mem = mmap(NULL, len, PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (mem == MAP_FAILED)            //出错判断
        sys_err("mmap err: ");
    close(fd);

    strcpy(mem, "aaa");
    printf("%s\n", mem);

    if (munmap(mem,  len) < 0)
        sys_err("munmap");

    return 0;
}

//思考：
//1. 如果mem++，munmap可否成功？
//2. 如果open时O_RDONLY, mmap时PROT参数指定PROT_READ|PROT_WRITE会怎样？
//3. 如果文件偏移量为1000会怎样？
//4. 如果不检测mmap的返回值，会怎样？
//5. mmap什么情况下会调用失败？
//6. 对mem越界操作会怎样？
//7. 文件描述符先关闭，对mmap映射有没有影响？
//8. 可以open的时候O_CREAT一个新文件来创建映射区吗?
