/* iolib.c 自己的文件I/O函数库 */
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
/* 封装read函数，增加可出错处理，参数和返回值和read函数相同 */
ssize_t my_read(int fd, void *buffer, size_t length) 
{
	ssize_t done = length;		/* 读入的字节数 */
	while(done > 0) { /* 如果因为信号中断而导致异常，则多次读取 */
		done = read(fd, buffer, length); /* 调用read函数 */
		if(done == -1)		/* 异常出错 */
			if(errno == EINTR)	/* 如果是信号中断导致的错误，则舍弃已读入的内容，重新读取 */
				done = length;
			else{
				perror("fail to read");	/* 其他错误则输出错误原因，并且返回 */
				return -1; 
			}
		else
			break;
	}
	return done;						/* 返回实际读入的字节数 */
}
/* 封装write函数，增加可出错处理，参数和返回值和write函数相同 */
ssize_t my_write(int fd, void *buffer, size_t length) 
{
	ssize_t done = length;		/* 实际写的字节数 */
	while(done > 0) { /* 如果因为信号中断而导致异常，则多次写缓冲区 */
		done = write(fd, buffer, length); /* 调用write函数 */
		if(done != length)		/* 异常出错 */
			if(errno == EINTR)	/* 如果是信号中断导致的错误，则舍弃已写的内容，重新写缓冲区 */
				done = length; 
			else{
				perror("fail to write"); /* 其他错误则输出错误原因，并且返回 */
				return -1; 
			}
		else
			break;
	}
	return done; /* 返回实际写的字节数 */
}

