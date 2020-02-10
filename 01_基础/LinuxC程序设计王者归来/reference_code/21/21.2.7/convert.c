#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define FILE_LEN 64
#define MAX_LINE 128
#define LINE 28
int main(int argc, char *argv[])
{
	FILE *in, *out;
	char file_name[FILE_LEN];
	char buf[MAX_LINE];
	char outbuf[MAX_LINE];
	char head[LINE];
	char *p;
	int len;
	if(argc != 2){ /* 命令格式错误，正确的格式为：命令名 配置文件名 */
		printf("wrong usage\n");
		exit(1);
	}
	len = strlen(argv[1]); /* 求文件名长度 */
	if(strcmp(&argv[1][len - 3], "ini") != 0){ /* 比较其扩展名是否是“ini” */
		printf("source file error\n");
		exit(1);
	}
	in = fopen(argv[1], "r"); /* 打开配置文件 */
	if(in == NULL){
		perror("fail to open");
		exit(1);
	}
	strcpy(file_name, argv[1]); /* 将配置文件的扩展名改为“xml” */
	strcpy(&file_name[len - 3], "xml");
	
	out = fopen(file_name, "w"); /* 打开“.xml”文件，该文件的文件名和原配置文件一样 */
	if(out == NULL){
		perror("fail to open");
		exit(1);
	}
	while(fgets(buf, MAX_LINE, in) != NULL){ /* 顺序读取每一行 */
		len = strlen(buf); /* 去掉最后一个‘\n’结束符 */
		printf("%d\n",len);
		buf[len - 1] = '\0';
		if(buf[0] == '#') /* 书写配置信息头 */
			sprintf(outbuf, "<!-- %s -->\n", buf);
		else if(buf[0] == '!'){ /* 书写配置信息头 */
			sprintf(outbuf, "<%s>\n", &buf[1]);
			strcpy(head, buf); /* 复制一份，用于后面输出</head> */
		}else if(buf[0] == '\0')
			sprintf(outbuf, "</%s>\n\n", &head[1]); /* 遇到空行，说明一个配置信息结束，输出配置信息结尾 */
		else{
			p = strtok(buf, "="); /* 将原配置文件中的一行拆分为配置选项和配置内容 */
			sprintf(outbuf, "\t<%s>%s</%s>\n", buf, p, buf);
		}
		if(fputs(outbuf, out) == -1){ /* 将准备好的输出信息输出，每一行输出一次 */
			perror("fail to write");
			exit(1);
		}
	}
	if(errno != 0){ /* 循环结束，判断是否是因为文件读操作出错而退出 */
		perror("fail to read");
		exit(1);
	}
	fclose(in); /* 关闭文件 */
	fclose(out);
	return 0;
}
