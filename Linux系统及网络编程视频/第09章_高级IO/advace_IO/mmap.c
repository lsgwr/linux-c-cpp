#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



void print_err(char *str, int line, int err_no)
{
        printf("%d, %s: %s\n", line, str, strerror(err_no));
        exit(-1);
}

int main(void)
{
	int srcfd = -1;
	int dstfd = -1;
	void *srcaddr = NULL;
	void *dstaddr = NULL;

	
	/* 打开源文件 */
	srcfd = open("./file_lock.h", O_RDWR);
	if(srcfd == -1) print_err("open file_lock.h fial", __LINE__, errno); 	
	
	/* 打开目标文件 */
	dstfd = open("./file", O_RDWR|O_CREAT|O_TRUNC, 0664);
	if(dstfd == -1) print_err("open file fial", __LINE__, errno); 	
	
	/* mmap映射源文件 */	
	struct stat src_stat = {0};
	fstat(srcfd, &src_stat);//获取文件属性(主要是想得到文件的size)
	srcaddr = mmap(NULL, src_stat.st_size, PROT_READ, MAP_SHARED, srcfd, 0);
	if(srcaddr == (void *)-1) print_err("mmap srcfile fail", __LINE__, errno);
	
	/* mmap映射目标文件 */	
	ftruncate(dstfd, src_stat.st_size);
	/*
	参数1:指定映射的起始虚拟地址,如果制定NULL表示由mmap指定
	参数2: 要映射的长度
	参数3:指定映射后的操作权限,PROT_WRITE/PROT_READ/PROT_EXEC/PROT_NONE
	参数4:是否立即更新到文件中,指定MAP_SHARED,表示理解更新
	参数5:你要映射的那个文件的fd
	参数6:指定一个偏移,表示你要从文件的什么位置开始映射 */
	dstaddr = mmap(NULL, src_stat.st_size, PROT_WRITE, MAP_SHARED, dstfd, 0);
	if(dstaddr == (void *)-1) print_err("mmap dstfile fail", __LINE__, errno);	
	
	
	/* 想办法讲源文件的数据复制到目标文件中 */
	memcpy(dstaddr, srcaddr, src_stat.st_size);

	
	return 0;	
}	
	
