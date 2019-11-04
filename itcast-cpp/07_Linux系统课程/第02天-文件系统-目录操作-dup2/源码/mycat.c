#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void my_err(int ret, char *str)
{
    if (ret == -1) {
        perror(str);
        exit(1);
    }
}

int main(int argc, char * argv[])
{
    char buf[1024];
    int ret;
    if (argc == 4) {
        if (strcmp(argv[2], ">") == 0) {
            int fd2 = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0664);
            dup2(fd2, STDOUT_FILENO);  //0in  1out  2err  
        }
    }
    int fd = open(argv[1], O_RDONLY);

    while ((ret = read(fd, buf, sizeof(buf)))) {
        write(STDOUT_FILENO, buf, ret);
    }

    return 0;
}
