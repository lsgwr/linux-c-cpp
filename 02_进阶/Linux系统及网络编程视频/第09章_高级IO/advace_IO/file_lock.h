#ifndef H_FILELOCK_H
#define H_FILELOCK_H

#include <unistd.h>
#include <fcntl.h>

//非阻塞设置写锁
#define SET_WRFLCK(fd, l_whence, l_offset, l_len)\
	set_filelock(fd, F_SETLK, F_WRLCK, l_whence, l_offset, l_len)
//阻塞设置写锁
#define SET_WRFLCK_W(fd, l_whence, l_offset, l_len)\
	set_filelock(fd, F_SETLKW, F_WRLCK, l_whence, l_offset, l_len)

//非阻塞设置读锁
#define SET_RDFLCK(fd, l_whence, l_offset, l_len)\
	set_filelock(fd, F_SETLK, F_RDLCK, l_whence, l_offset, l_len)
//阻塞设置读锁
#define SET_RDFLCK_W(fd, l_whence, l_offset, l_len)\
	set_filelock(fd, F_SETLKW, F_RDLCK, l_whence, l_offset, l_len)

//解锁
#define UNLCK(fd, l_whence, l_offset, l_len)\
	set_filelock(fd, F_SETLK, F_UNLCK, l_whence, l_offset, l_len)

/* 调用这个函数,即可实现阻塞加读锁/阻塞加写锁, 非阻塞加读锁/非阻塞加写锁/解锁 */
static void set_filelock(int fd, int ifwait, int l_type, int l_whence, int l_offset, int l_len)
{
	int ret = 0;	
	struct flock flck;
	
	flck.l_type = l_type;
	flck.l_whence = l_whence;
	flck.l_start = l_offset;
	flck.l_len = l_len;

	ret = fcntl(fd, ifwait, &flck);
	if(ret == -1)
	{
		perror("fcntl fail");
		exit(-1);
	}
} 



#endif


