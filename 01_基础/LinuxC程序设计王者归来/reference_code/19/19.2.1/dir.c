#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
int main(void)
{
	if(mkdir("/home/linux-c/tmp", S_IRUSR | S_IWUSR | S_IXUSR) == -1){ /* 创
															建一个目录 */
		perror("fail to mkdir");
		exit(1);
	}
	printf("successfully make a dir\n"); /* 输出提示信息 */
	return 0;
}
