#include <stdio.h>
extern ** environ; /* 环境变量表的指针 */
int main()
{
	int i;
	/*遍历打印环境变量，但是这种方法并不是被推荐的。
	*原因会在后面的章节详细说明，这里的代码只是为了演示环境变量
	*/
	for(i = 0; environ[i] != NULL; i++) 
		printf("each : %s\n", environ[i]);
	return 0;
}
