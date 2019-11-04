#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	void *p; 					/* p是一个void *类型的指针 */
	int *q;
	p = malloc(sizeof(int));	/* 使用malloc函数分配4个字节 */
	if(p == NULL){
		perror("fail to malloc");
		exit(1);
	}
	
	q = (int *)p; /* 需要将p转换为指向整型的指针后才可以应用其指向的数据 */
	*q = 100;	
	 
	printf("the value is : %d\n", *q);

	return 0;
}
