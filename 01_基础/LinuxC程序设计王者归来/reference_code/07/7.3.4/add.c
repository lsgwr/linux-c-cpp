void f( )
{
	int static count = 10;	/* 静态局部变量，局部符号 */
	int a = 0;				/* 局部变量 */
	count++;				/* 静态局部变量累加 */
	if(count >= 20)
		goto done;			/* 局部标号 */
	else{
		printf("the count is lower than 20\n");
		return ;
	}
done:						/* 局部标号 */
	printf("the count is higher than 20\n");
	a = 20;					/* 对局部变量赋值 */
	printf("a is : %d\n", a);
	return ;
}
