#include <stdio.h>

int main(void)
{	
	int score;

	scanf("%d", &score);	/* 输入分数 */

	switch(score){			/* 根据输入的字符判断应该执行哪一个执行语句 */
	case 'A':				/* 分数为A */
		printf("90 ~ 100\n");
		break;
	case 'B':				/* 分数为B */
		printf("80 ~ 90\n");
		break;
	case 'C':				/* 分数为C */
		printf("70 ~ 80\n");
		break;
	case 'D':				/* 分数为D */
		printf("60 ~ 70\n");
		break;
	case 'E':				/* 分数为E */
		printf("0 ~ 50\n");
		break;
	default:						/* 错误输入 */
		printf("wrong input\n");	/* 默认的执行语句 */

	return 0;
}
}

