#include "common.h"
int main(void)
{
	int a, b;
	sacnf("%d %d", &a, &b);
	swap(a, b);
	printf("%d, %d\n", a, b);
	return 0;
}
