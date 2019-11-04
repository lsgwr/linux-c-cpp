#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
/* 读操作掩码，将所有者用户、组用户和其他用户的读权限全部添加 */
#define READ_MASK S_IRUSR | S_IRGRP | S_IROTH
/* 写操作掩码，将所有者用户、组用户和其他用户的写权限全部添加 */
#define WRITE_MASK S_IWUSR | S_IWGRP | S_IWOTH
int main(void)
{
	int fd;
	struct stat statbuf;
	/* 打开一个文件，如果该文件不存在，则使用读操作掩码作为权限字创建该文件 */
	if((fd = open("test.txt", O_RDONLY | O_CREAT, READ_MASK)) == -1){
		perror("fail to open");
		exit(1);
	}
	printf("before changing model\n"); /* 输出提示信息 */
	if(fstat(fd, &statbuf) == -1){ /* 在打开的文件上得到文件状态 */
		perror("fail to get status");
		exit(1);
	}
	if(statbuf.st_mode & S_IRUSR) /* 所有者用户具有读文件的权限 */
		printf("user can read\n");
	if(statbuf.st_mode & S_IRGRP) /* 组用户具有读文件的权限 */
		printf("group user can read\n");
	if(statbuf.st_mode & S_IROTH) /* 其他用户具有读文件的权限 */
		printf("other user can read\n");
	printf("\n");
	/* 使用写操作权限字改变文件的权限，
	* 改变后文件的所有读权限消失，
	* 取而代之的是所有的写权限 
	*/
	if(fchmod(fd, WRITE_MASK) == -1){
		perror("fail to change model");
		exit(1);
	}
	printf("after changing model\n");
	if(fstat(fd, &statbuf) == -1){ /* 再次取得文件的状态 */
		perror("fail to get status");
		exit(1);
	}
	printf("check the file by file-descriptor\n");
	/* 直接使用该文件的描述符取得文件状态，检查文件权限是否更新 */
	if(statbuf.st_mode & S_IWUSR) /* 所有者用户具有写文件的权限 */
		printf("user can write\n");
	if(statbuf.st_mode & S_IWGRP) /* 组用户具有写文件的权限 */
		printf("group user can write\n");
	if(statbuf.st_mode & S_IWOTH) /* 其他用户具有写文件的权限 */
		printf("other user can write\n");
	printf("\n");
	/* 再次从磁盘上取得该文件的文件状态，检查磁盘上的文件权限是否也已经更新 */
	if(stat("test.txt", &statbuf) == -1){
		perror("fail to get status"); 
		exit(1);	
	}
	printf("check the file in the disk\n");
	/* 磁盘上的文件权限也已经更新 */
	if(statbuf.st_mode & S_IWUSR) /* 所有者用户具有写文件的权限 */
		printf("user can write\n");
	if(statbuf.st_mode & S_IWGRP) /* 组用户具有写文件的权限 */
		printf("group user can write\n");
	if(statbuf.st_mode & S_IWOTH) /* 其他用户具有写文件的权限 */
		printf("other user can write\n");	
	printf("\n");
	sleep(10); 		/* 休眠10秒钟 */
	printf("done\n"); /* 打印提示信息 */
	close(fd); 		/* 文件关闭，所有缓冲区的内容冲洗到磁盘上 */
	return 0;
}
