#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
int main(void)
{
	struct stat buf; /* 存储文件状态信息 */
	if(lstat("sl", &buf) == -1){
		perror("fail to stat");
		exit(1);
	}
	printf("*********sl***********\n");
	printf("permission : %d\n", (int)buf.st_mode); 	/*打印符号链接的文件权限字 */
	printf("inode number : %d\n", (int)buf.st_ino);	/* 打印符号链接的i节点号 */
	printf("device number : %d\n", (int)buf.st_dev); 	/* 打印符号链接的文件系统
													设备号 */
	printf("r-device number : %d\n", (int)buf.st_rdev);	/* 打印符号链接的硬件设备
													设备号 */
	printf("link : %d\n", (int)buf.st_nlink); 			/* 打印符号链接的硬链接数 
													*/
	printf("uid : %d\n", (int)buf.st_uid);				/* 打印符号链接的所有者用
													户ID */
	printf("gid : %d\n", (int)buf.st_gid); 				/* 打印符号链接的所有者组
													ID */
	printf("file size : %d\n", (int)buf.st_size); 		/* 打印符号链接的文件的大
													小 */
	printf("access time : %d\n", (int)buf.st_atime); 	/* 打印符号链接的最近一次
													的访问时间*/
	printf("motify time : %d\n", (int)buf.st_mtime); 	/* 打印符号链接的最近一次
													修改文件内容的时间 */
	printf("change time : %d\n", (int)buf.st_ctime); 	/* 打印符号链接的最近一次
													修改文件属性的时间 */
	printf("buf size : %d\n", (int)buf.st_blksize); 	/* 打印符号链接的最适合的
													缓冲区大小 */
	printf("block size : %d\n", (int)buf.st_blocks); 	/* 打印符号链接的文件在外
													存上占用的盘块数 */
	if(stat("test.txt", &buf) == -1){
		perror("fail to stat");
		exit(1);
	}
	printf("*********test.txt***********\n");
	printf("permission : %d\n", (int)buf.st_mode); 		/* 打印目的文件的文件权限
													字 */
	printf("inode number : %d\n", (int)buf.st_ino); 	/* 打印目的文件的i节点号 
													*/
	printf("device number : %d\n", (int)buf.st_dev);		/* 打印目的文件的文件系统			设备号 */
	printf("r-device number : %d\n", (int)buf.st_rdev);	/* 打印目的文件的硬件设备
													设备号 */
	printf("link : %d\n", (int)buf.st_nlink);			/* 打印目的文件的硬链接数 
													*/
	printf("uid : %d\n", (int)buf.st_uid); 				/* 打印目的文件的所有者用
													户ID */
	printf("gid : %d\n", (int)buf.st_gid); 				/* 打印目的文件的所有者组
													ID */
	printf("file size : %d\n", (int)buf.st_size);		/* 打印目的文件的文件大小 
													*/
	printf("access time : %d\n", (int)buf.st_atime);	/* 打印目的文件最近一次的
													访问时间*/
	printf("motify time : %d\n", (int)buf.st_mtime);	/* 打印目的文件最近一次修
													改文件内容的时间 */
	printf("change time : %d\n", (int)buf.st_ctime);/* 打印目的文件最近一次修改文
												件属性的时间 */
	printf("buf size : %d\n", (int)buf.st_blksize); /* 打印目的文件最适合的缓冲
												区大小 */
	printf("block size : %d\n", (int)buf.st_blocks); /* 打印目的文件在外存上占用
												的盘块数 */
	return 0;
}
