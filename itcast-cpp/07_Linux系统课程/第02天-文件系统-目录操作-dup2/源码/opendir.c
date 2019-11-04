#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

int main(void)
{
    DIR *dp;
    struct dirent *sd = NULL;
    dp = opendir("/home/itcast/0611_comm");
    if (dp == NULL) {
        perror("open testdir111");
        exit(1);
    }

    while (sd = readdir(dp)) {
        printf("%s\n", sd->d_name);
    }

    printf("------------\n");

    closedir(dp);

    return 0;
}


