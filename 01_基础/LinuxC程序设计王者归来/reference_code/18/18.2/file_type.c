#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
int main(int argc, char * argv[])
{
	char *str;
	int i;
	struct stat buf;						/* 存储文件状态信息 */
	for(i = 1; i < argc; i++){
		printf("%s is ", argv[i]);
		if(stat(argv[i], &buf) == -1){ 		/* 得到文件的状态 */
			perror("fail to stat");
			exit(1);
		}
		
		if(S_ISREG(buf.st_mode)) 			/* 普通文件 */
			printf("regular file \n");
		else if(S_ISDIR(buf.st_mode)) 		/* 目录文件 */
			printf( "directory file\n");
		else if(S_ISCHR(buf.st_mode)) 		/* 字符特殊文件 */
			printf( "character special file\n");
		else if(S_ISBLK(buf.st_mode)) 		/* 块特殊文件 */
			printf( "block special file\n");
		else if(S_ISFIFO(buf.st_mode)) 		/*命名管道文件 */
			printf( "FIFO file\n");
		else if(S_ISSOCK(buf.st_mode)) 	/* 套接字文件 */
			printf( "socket file\n");
		else 								/* 未知类型 */
			printf( "unkonw\n");
	}
	return 0;
}
