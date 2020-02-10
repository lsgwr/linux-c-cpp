#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
	if(symlink("test.txt", "symbol_link") == -1){ /* 创建一个符号链接 */
		perror("fail to create symbol link");
		exit(1);
	}
	printf("create a new symbol-link\n"); /* 输出提示信息 */
	return 0;
}
