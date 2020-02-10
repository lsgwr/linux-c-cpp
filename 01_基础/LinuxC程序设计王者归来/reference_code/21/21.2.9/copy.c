#include <stdio.h>
#include <stdlib.h>
/* 程序使用方法：copy src des
*  本程序并未做输入的出错处理，例如，文件路径的正确性以及目标文件是否已经存在等
*/
int main(int argc, char *argv[ ])
{
	FILE *fp1, *fp2; /* 源文件和目标文件 */
	char buf[1024];
	int nbytes;
	if(argc != 3){ /* 检查参数个数 */
		printf("wrong command\n");
		exit(1);
	}
	if((fp1 = fopen(argv[1], "rb")) == NULL){ /* 打开源文件 */
		perror("fail to open");
		exit(1);
	}
	if((fp2 = fopen(argv[2], "wb")) == NULL){ /* 打开目标文件 */
		perror("fail to open");
		exit(1);
	}
/* 开始复制文件，文件可能很大，缓冲一次装不下，所以使用一个循环进行读写 */
	while((nbytes = fread(buf, sizeof(char), 1024, fp1)) > 0){ /* 读源文件，直到将文件内容全部读完 */
		if(fwrite(buf, sizeof(char), nbytes, fp2) == -1){ /* 将读出的内容全部写到目标文件中去 */
			perror("fail to write");
			exit(1);
		}
	}
	if(nbytes == -1){ /* 如果因为读入字节小于0而跳出循环，则说明出错了 */
		perror("fail to read");
		exit(1);
	}
	fclose(fp1); /* 关闭源文件和目标文件 */
	fclose(fp2);
	return 0;
}
