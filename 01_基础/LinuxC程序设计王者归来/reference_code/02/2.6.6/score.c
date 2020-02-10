#include <stdio.h>

int main(void)
{	
	int score;

	scanf("%d", &score);	/* 输入分数 */

	if(score == 'A')		/* 分数为A */
		printf("90 ~ 100\n");
	else if(score == 'B')	/* 分数为B */
		printf("80 ~ 90\n");
	else if(score == 'C')	/* 分数为C */
		printf("70 ~ 80\n");
	else if(score == 'D')	/* 分数为D */
		printf("60 ~ 70\n");
	else if(score == 'E')	/* 分数为E */
		printf("0 ~ 50\n");
	else					/* 错误输入 */
		printf("wrong input\n");

	return 0;
}

