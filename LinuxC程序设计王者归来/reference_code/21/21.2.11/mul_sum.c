#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#define MAX_LINE 128
#define FILE_SIZE 1024
int main(void)
{
	FILE *in, *out;
	FILE *fp;
	struct stat statbuf;
	char file_name[MAX_LINE];
	char *buf;
	int n,len;
	char *p;
	int file_size = 0;
	int letter, number, blank;
	if(system("ls > temp") == -1){ /* 使用system函数执行ls命令，得到当
										前目录下的文件列表 */
		perror("fail to exec command");
		exit(1);
	}
	fp = fopen("temp", "rb"); /* 打开保存文件列表的文件 */
	if(fp == NULL){
		perror("fail to open");
		exit(1);
	}
	out = fopen("res", "wb"); /* 打开保存文件信息的文件 */
	if(out == NULL){
		perror("fail to open");
		exit(1);
	}
	while(fgets(file_name, MAX_LINE, fp) != NULL){ /* 读取一个文件名 */
		len=strlen(file_name);
		if(strcmp(&file_name[len-4], "txt\n") != 0)
			continue;
		file_name[len-1]='\0';
		if(stat(file_name, &statbuf) == -1){ /* 得到文件的状态，该状态中包含文
										          件的大小 */
			perror("fail to get stat");
			exit(1);
		}
		
		if(S_ISDIR(statbuf.st_mode)) /* 如果该文件是一个子目录，则跳过 */
			continue;
		/* 最大分配FILE_SIZE个字节的缓冲区，如果文件太大则需要分批读入
		* 小于或者等于1024字节的文件都能够一次性读入到内存中
		*/
		if((file_size = statbuf.st_size) > FILE_SIZE)
			file_size = FILE_SIZE;
		file_size++; /* 多出一个位置用于设置'\0'结束符 */
		buf = (char *)malloc(sizeof(char) *file_size); /* 分配缓冲区 */
		in = fopen(file_name, "rb"); 					/* 打开该文件 */
		if(in == NULL){
			perror("fail to open");
			exit(1);
		}
		letter = 0;
		number = 0;
		blank = 0;
		/* 循环读取文件的内容，对于小文件只需要一次读入；对于大文件需要多次读入 */
		while((n = fread(buf, sizeof(char), file_size - 1, in)) > 0){
			buf[n] = '\0'; 								/* 手动设置结束符 */
			p = buf;
			while(*p != '\0'){ /* 处理每次读入的文件内容 */
				if(('a' <= *p && *p <= 'z') || ('A' <= *p && *p <= 'Z')) 
				/* 判断为字母 */
					letter++;
				if(*p == ' ') 	/* 判断为空格 */
					blank++;
				if('0' <= *p && *p <= '9') 				/* 判断为数字 */
					number++;
				p++;
			}
		}
		if(n == -1){ /* 读操作出错 */
			perror("fail to read");
			exit(1);
		}
		/* 输出结果，字母数、数字数和空格数 */
		fprintf(out,"%s, he sum of letter is : %d\nthe sum of number is : %d\nthe sum of blank is : %d\n", file_name, letter, number, blank);
		fclose(in);
		free(buf); /* 需要释放缓冲区，下一次会分配新的缓冲区 */
	}
	fclose(fp);
	fclose(out);
	if(unlink("temp") == -1){ /* 删除保存临时文件的temp.txt文件 */
		perror("fail to unlink");
		exit(1);
	}
	return 0;
}
