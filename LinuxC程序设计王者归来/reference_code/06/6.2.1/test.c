#include <stdio.h>
int add(int a, int b) 
{ 
	return a + b;
}
int main(void) 
{
	int i, sum;
	for (i = 0; i < 3 ; i++){
		sum = add(i, i + 1);
		printf("%d\n", sum); 
	}
}

