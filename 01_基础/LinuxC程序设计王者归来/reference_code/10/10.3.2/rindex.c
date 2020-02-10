#include <stdio.h>
#include <string.h>
/* 得到一个完整路径中的最后的文件名 */
char* basename(char*  full_name)
{
		char *p;
		p = rindex(full_name,'/');	/* 找到路径名中第一个"/" */
		if (p == '\0')  	
			p = full_name;			/* 找不到‘/‘说明已经是一个文件名 */
		else 
			p++;					/* 得到文件名的起始位置 */
		return p;					/* 返回文件名 */
}
int main(int argc, char * argv[])
{
	char *p;
	p = basename(argv[0]); /* 将第一个命令行参数中的程序文件名提取出来 */
	printf("file name is : %s\n", p); /* 输出文件名 */
	return 0;
}
