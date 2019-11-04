#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
	if(rmdir("./dir") == -1){ /*输出一个目录 */
		perror("fail to rmkdir");
		exit(1);
	}
	printf("successfully remove a dir\n"); /* 输出提示信息 */
	return 0;
}
