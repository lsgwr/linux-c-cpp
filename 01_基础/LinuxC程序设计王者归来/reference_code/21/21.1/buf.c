#include <stdio.h>
int main(void)
{	
	printf("stdin is ");
	if(stdin->_flags & _IO_UNBUFFERED) /* 判断标准输入流对象的缓冲区类型*/
		printf("unbuffered\n");
	else if(stdin->_flags & _IO_LINE_BUF)
		printf("line-buffered\n");
	else
		printf("fully-buffered\n");
	printf("buffer size is %d\n", stdin->_IO_buf_end - stdin->_IO_buf_base); /* 输出缓冲区的大小 */
	printf("discriptor is %d\n\n", fileno(stdin)); /* 输出文件描述符 */
	printf("stdout is ");
	if(stdout->_flags & _IO_UNBUFFERED) /* 判断标准输出流对象的缓冲区类型*/
		printf("unbuffered\n");
	else if(stdout->_flags & _IO_LINE_BUF)
		printf("line-buffered\n");
	else
		printf("fully-buffered\n");
	printf("buffer size is %d\n", stdout->_IO_buf_end - stdout->_IO_buf_base); /* 输出缓冲区的大小 */
	printf("discriptor is %d\n\n", fileno(stdout)); /* 输出文件描述符 */
	printf("stderr is ");
	if(stderr->_flags & _IO_UNBUFFERED) /* 判断标准出错流对象的缓冲区类型*/
		printf("unbuffered\n");
	else if(stderr->_flags & _IO_LINE_BUF)
		printf("line-buffered\n");
	else
		printf("fully-buffered\n");
	printf("buffer size is %d\n", stderr->_IO_buf_end - 	stderr->_IO_buf_base); /* 输出缓冲区的大小 */
	printf("discriptor is %d\n\n", fileno(stderr)); /* 输出文件描述符 */
	return 0;
}
