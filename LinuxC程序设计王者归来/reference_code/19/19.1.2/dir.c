#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
int main(void)
{
	struct stat buf; /* 存储文件状态信息 */
	if(stat("/home/linux-c", &buf) == -1){ /* 得到文件状态信息 */
		perror("fail to stat");
		exit(1);
	}
	if(!S_ISDIR(buf.st_mode)){ /* 非目录文件 */
		printf( "this is not a directory file\n");
		exit(1);
	}
	if(S_IRUSR & buf.st_mode) /* 所有者用户具有读目录权限 */
		printf("user can read the dir\n");
	if(S_IWUSR & buf.st_mode) /* 所有者用户具有写目录权限 */
		printf("user can write the dir\n");
	if(S_IXUSR & buf.st_mode) /* 所有者用户具有执行目录权限 */
		printf("user can through the dir\n");
	return 0;
}
