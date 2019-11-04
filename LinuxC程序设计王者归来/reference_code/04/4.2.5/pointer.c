#include <stdio.h>

struct test{ /* 声明一个结构体，不考虑对齐机制的话，每个该结构变量占用9个字节 */
	int array[2];
	char ch;
};

typedef struct test Test;

int main(void)
{
	Test var = {0x12345678,0x12345678, 0x30}; /* 初始化结构体变量 */
	char *p;
	Test *q;
	/* 将指针p转换为指向字符型变量，向后看1个字节 */
	p = (char *)&var;
	printf("1 byte : 0x%x\n", *p);

	/* 将指针p转换为指向短整型变量，向后看2个字节 */
	printf("2 bytes : 0x%x\n", *(short *)p);

	/* 将指针p转换为指向整型变量，向后看4个字节 */
	printf("4 bytes : 0x%x\n", *(int *)p);

	/* 将指针p转换为指向长整型(long long型)变量，向后看8个字节 */
	printf("8 bytes : 0x%llx\n", *(long long *)p);

	/* 将指针p转换为指向test结构类型的变量，向后看9个字节 */
	q = (Test *)p;
	printf("whole bytes : 0x%x, 0x%x, %c\n", q->array[0], q->array[1], q->ch);

	return 0;
}

