#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[ ])
{
	FILE *fp1, *fp2; /* 源文件和目标文件 */
	int c;
	if(argc != 3){ /* 检查参数个数 */
		printf("wrong command\n");
		exit(1);
	}
	if((fp1 = fopen(argv[1], "r")) == NULL){ /* 打开源文件 */
		perror("fail to open");
		exit(1);
	}
	if((fp2 = fopen(argv[2], "w+")) == NULL){ /* 打开目标文件 */
		perror("fail to open");
		exit(1);
	}
	/* 开始复制文件，每次读写一个字符 */
	while((c = fgetc(fp1)) != EOF){ /* 读源文件，直到将文件内容全部读完 */
		if(fputc(c, fp2) == EOF){ /* 将读入的字符写到目标文件中去 */
			perror("fail to write");
			exit(1);
		}
		if(fputc(c, stdout) == EOF){ /* 将读入的字符输出到屏幕 */
			perror("fail to write");
			exit(1);
		}
	}
	if(errno != 0){ /* 如果errno变量不为0说明出错了 */
		perror("fail to read");
		exit(1);
	}
	fclose(fp1); /* 关闭源文件和目标文件 */
	fclose(fp2);
	return 0;
}

