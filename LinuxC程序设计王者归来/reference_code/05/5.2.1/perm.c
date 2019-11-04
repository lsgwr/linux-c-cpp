#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void)
{
	struct stat statbuf;
	int mask = 0x1ff; /* Linux文件的权限位在Linux文件状态字的第9位 */
	int status = 0;

	if(stat("test.txt", &statbuf) == -1){	/* 得到文件状态字，内含有Linux文
											件的权限标志位 */
		perror("fail to get stat");
		exit(1);
	}

	status = statbuf.st_mode & mask;				/* 通过掩码将权限更改 */
	printf("the permission is : 0x%x\n", status);	/* 输出文件的权限 */

	return 0;
}
