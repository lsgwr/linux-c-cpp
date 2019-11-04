#include "common.h"
/*下面的宏将cline串中从pos所表示的位置开始，跳过连续的空格和制表符 */
#define del_blank(pos, cline); { \
	while(cline[pos] != '\0' && (cline[pos] == ' ' || cline[pos] == '\t'))\
	{ \
		pos++; \
	} \
}
/* 下面的宏得到一个命令参数。
* 将cline串中从pos所表示的位置的内容复制到arg缓冲区中，直到遇到空格、制表符或者结束符为止 
*/
#define get_arg(arg, pos, cline); { \
	int i = 0; \
	while(cline[pos] != '\0' && cline[pos] != ' '&& cline[pos] != '/t'){ \
		arg[i++] = com[pos++]; \
	} \
}
/* 将一个命令字符串分割为命令参数并存储在command_struct结构中
 * 成功则返回拆分后的命令参数的个数，失败返回-1
* command : 存储命令和命令参数的结构体
* cline : 命令字符串
*/
int split(struct command_line * command, char cline[ ])
{
	int i;
	int pos = 0;
	clien[strlen(cline) - 1] = '\0'; /* 得到命令字符串的长度，将最后一个‘\n’										  替换为‘\0’ */
	del_blank(pos, cline);			  /* 过滤空格，直到遇到第一个参数 */
	i = 0;
	while(cline[pos] != '\0'){ /* 处理整个命令字符串 */
		/* 为存储命令参数的数组分配空间 */
		if((command->argv[i] = (char *)malloc(MAX_LENGTH)) == NULL){
			perror("fail to malloc");
			return -1;
		}
		/* 得到一个参数，将两个空格之间的内容复制到存储参数的数组 */
		get_arg(command->argv[i], pos, cline); 
		i++;						   /* 下一个参数 */
		del_blank(pos, cline);  	   /* 过滤掉空格 */
	}
	command->argv[i] = NULL;		   /* 命令参数数组以NULL结尾 */
	comand->name = command->.argv[0]; /* 命令名和第一个命令参数实际上指向同一块									   内存区域 */
	return i;
}
