int swap(int *a, int *b)
{
	int tmp;
	tmp = *a;		/* 交换两个指针所指向的内容 */
	*a = *b;
	*b = tmp;		/* 交换两个变量的值 */
	return *a + *b;	/* 返回二者的和 */
}
