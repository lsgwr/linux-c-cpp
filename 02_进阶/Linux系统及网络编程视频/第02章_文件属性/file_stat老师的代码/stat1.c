#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>



void print_error(char *str)
{
	perror(str);
	exit(-1);
}


void ls_fun(char *file_name)
{
	int ret = 0;
	int i = 0;
	struct stat sta = {0};

	/* 获取文件属性 */
	ret = lstat(file_name, &sta);
	if(-1 == ret) print_error("-lstat fail");

	
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
		sta.st_uid, sta.st_gid, sta.st_size, sta.st_atime, file_name);

	if(file_type == 'l')
	{
		char sym_buf[30]  = {0};
		readlink(file_name, sym_buf, sizeof(sym_buf));
		printf(" -> %s\n", sym_buf);
	}
	else printf("\n");
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
	ret = lstat(argv[1], &sta);
	if(-1 == ret) print_error("lstat fail");

	
	/* 打印文件类型 */
	char file_type = '0';	

	if(S_ISLNK(sta.st_mode)) file_type = 'l'; 
	else if(S_ISREG(sta.st_mode)) file_type = '-';
	else if(S_ISDIR(sta.st_mode)) file_type = 'd';
	else if(S_ISCHR(sta.st_mode)) file_type = 'c';
	else if(S_ISBLK(sta.st_mode)) file_type = 'b';
	else if(S_ISFIFO(sta.st_mode)) file_type = 'p';
	else if(S_ISSOCK(sta.st_mode)) file_type = 's';
	
	if(file_type != 'd') 
	{
		ls_fun(argv[1]);
	}
	else
	{	
		char pwd[100] = {0};

		getcwd(pwd, sizeof(pwd));
		chdir(argv[1]);

		DIR *dirp = opendir(".");		
		
		while(1)
		{
			struct dirent *direntp = readdir(dirp);
			
			//printf("%s\n", direntp->d_name);
			
			if(direntp == NULL && errno == 0) break;
			ls_fun(direntp->d_name);
		}

		chdir(pwd);
	}	

	return 0;
}

