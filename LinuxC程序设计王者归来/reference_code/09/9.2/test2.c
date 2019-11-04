#include <stdio.h>
#include <stdlib.h>
int main(int argc,char * argv[])
{
	if(argc != 3){ /* 根据命令行参数个数输出程序使用方法 */
		printf("Usage:hello word1 word2 \n");
		exit(0);
	}
	printf("word1 is %s \n word2 is %s \n", argv[1], argv[2]);/* 输出两个
																   字符串*/
	return 0;
}
