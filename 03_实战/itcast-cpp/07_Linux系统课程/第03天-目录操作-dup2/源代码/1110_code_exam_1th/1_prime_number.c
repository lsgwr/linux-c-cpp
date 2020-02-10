#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int i, m, n;
	int count = 1;          //用来设置显示格式

    if (argc != 2) {
        printf("Enter: ./a.out number\n");
        exit(1);
    }

	printf("1～%d之间的素数有：\n", n = atoi(argv[1]));

	for (i = 2; i <= n; i++) {
		for(m = 2; m < i; m++) {
			if(i % m == 0) {
				break;
            }
		}
		if (m >= i)
			printf("%2d %c", i, (count++) % 10 ? ' ' : '\n');
	} 
	printf("\n");

	return 0;
}
