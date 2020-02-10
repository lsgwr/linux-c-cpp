#include <stdio.h>

int main(void)
{
	char score;
	
	scanf("%c", &score);	/* 输入分数 */

	switch(score){			/* 根据输入的分数，输出相应的提示信息 */
	case 'A': 
		printf("excellent\n");
		break; 				/* 注意，这个break语句是必须加上的 */
	case 'B': 
		printf("good\n");	/* 根据不同的分数输出各个提示信息 */
		break;
	case 'C': 
		printf("pass\n");
		break;
	default: 
		printf("fail\n");	/* 默认的提示信息 */
	}

	return 0;
}

