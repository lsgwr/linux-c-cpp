#include <stdio.h>
#include <arpa/inet.h> 		 /* 使用字节序转换函数的 */
int main(void)
{
	short a = htons(0x0102); /* 主机字节序转换位网络字节序 */
	short * p = &a;
	if( *((char*)p) == 0x01 ) /* 测试最低位的数据是多少 */
		printf("big-endian\n");
	else if(*((char*)p) == 0x02 )
		printf("little-endian\n");
	else
		printf("unknown\n"); /* 未知存储方法 */
	return 0;
}
