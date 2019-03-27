#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void print_error(char *str)
{
	perror(str);
	exit(-1);
}



int main(int argc, char **argv)
{
	int ret = 0;
	int i = 0;
	struct stat sta = {0};

	
	if(argc != 2)
	{
		printf("./a.out fileName\n\n");
		exit(-1);
	}

	/* 获取文件属性 */
	//int fd = open(argv[1], O_RDWR);
	//if(fd == -1)
	//{
	//	perror("open fail");
	//	exit(-1);
	//}
	//ret = fstat(fd, &sta);
	ret = lstat(argv[1], &sta);
	//ret = stat(argv[1], &sta);
	if(-1 == ret) print_error("stat fail");

	
	/* 打印文件类型 */
	char file_type = '0';	

	if(S_ISLNK(sta.st_mode)) file_type = 'l'; 
	else if(S_ISREG(sta.st_mode)) file_type = '-';
	else if(S_ISDIR(sta.st_mode)) file_type = 'd';
	else if(S_ISCHR(sta.st_mode)) file_type = 'c';
	else if(S_ISBLK(sta.st_mode)) file_type = 'b';
	else if(S_ISFIFO(sta.st_mode)) file_type = 'p';
	else if(S_ISSOCK(sta.st_mode)) file_type = 's';
	
	printf("%c", file_type);


	/* 打印文件权限 */	
	char buf[10] = {0};
	char tmp_buf[] = "rwxrwxrwx";
	for(i=0; i<9; i++)
	{
		if(sta.st_mode & (1<<(8-i))) buf[i] = tmp_buf[i];
		else buf[i] = '-';
	}
	
	printf("%s", buf);
	

	/* 打印文件属性 */
	printf(" %lu %u %d %ld %ld %s", sta.st_nlink, \
		sta.st_uid, sta.st_gid, sta.st_size, sta.st_atime, argv[1]);

	if(file_type == 'l')
	{
		char sym_buf[30]  = {0};
		readlink(argv[1], sym_buf, sizeof(sym_buf));
		printf(" -> %s\n", sym_buf);
	}
	else printf("\n");

	return 0;
}

