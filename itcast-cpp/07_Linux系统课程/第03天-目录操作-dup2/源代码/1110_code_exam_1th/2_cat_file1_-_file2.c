#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void sys_err(int fd, char *err_name)
{
	if(fd < 0){
		perror(err_name);
		exit(1);
	}
}

int main(void)
{
	int fd_f1, fd_f2, fd_out;
    int ret;
    char buf[1024];
    
	fd_f1 = open("file1", O_RDONLY);
sys_err(fd_f1, "open file1 error");

	fd_f2 = open("file2", O_RDONLY);
sys_err(fd_f2, "open file2 error");

	fd_out = open("out", O_WRONLY|O_TRUNC|O_CREAT, 0644);
sys_err(fd_out, "open out error");

	dup2(fd_out, STDOUT_FILENO);

    while ((ret = read(fd_f1, buf, sizeof(buf)))) {
	    write(fd_out, buf, ret);
    }

    while ((ret = read(STDIN_FILENO, buf, sizeof(buf)))) {
	    write(fd_out, buf, ret);
    }

    while ((ret = read(fd_f2, buf, sizeof(buf)))) {
	    write(fd_out, buf, ret);
    }

	close(fd_f1);
	close(fd_f2);
	close(fd_out);

	return 0;
}
