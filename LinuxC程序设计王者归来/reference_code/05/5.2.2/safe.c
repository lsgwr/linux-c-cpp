#include <stdio.h>

int main(void)
{
	int a = 0x1234567f;

	/* b为整数1取反，不论在32体系结构还是在16位体系结构上，
	* ~1均可保证最低位是"0"，而高位均为"1" 
	*/
	int b = ~1; 

	printf("the result is : 0x%x\n", a & b); /* 输出结果 */

	return 0;
}
