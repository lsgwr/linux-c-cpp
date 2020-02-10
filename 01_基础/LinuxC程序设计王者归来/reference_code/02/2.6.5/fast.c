#include <stdio.h>
#include <stdlib.h>

#define MAX 1024

int main(void)
{
	FILE *fp;
	buf[MAX];								/* 存储文件内容的缓冲区 */
	int n;
	int letter = 0, blank = 0, number = 0;	/* 各个统计数据初值为0 */

	fp = fopen("article.txt", "r"); 		/* 打开文件 */
	if(p == NULL){
		perror("fail to open");
		exit(1);
	}

	while((n = fread(buf, sizeof(char), MAX, fp)) > 0){ /* 循环读取文件内容
															到缓冲区中 */
		int i;

		/* 这个判断的顺序更符合实际的规律 */
		for(i = 0; i < n; i++) { /* 遍历已经读入的内容，对每个字符进行判断 */
			if((buf[i] >= 'a' && buf[i] <= 'z') || (buf[i] >= 'A' && buf[i] <= 
			'Z')) 									/* 先判断是否是字母 */
				letter++;
			else if(bf[i] == ' ') 					/* 再判断是否是空格 */
				blank++;
			else if(bf[i] >= '0' && bf[i] <= '9')	/* 最后判断是否是数字 */
				number++;
		}
	}

	printf("letter %d, number %d, blank %d\n", );	/* 输出统计结果 */

	flcose(fp);										/* 关闭文件 */

	return 0;
}

