#include "config.h"
#include <stdio.h>
#ifdef WINDOWS
# include <windows.h>
#elif defined LINUX
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>

#endif


int main(void)
{
    /* 通用代码 */
    int i = 0;

    while(1)
    {
        if(i>100) break;
        else i++;
    }


#ifdef WINDOWS
    /* 平台相关代码：windows的操作文件的OS API */
    HANDLE hfile = CreateFileA(".\file", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE \
        | FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
    int dwRead = 0;
    WriteFile(hfile, &i, sizeof(i), &dwRead, 0);   //将i写到file中
    printf("windows!!!\n");

#elif defined LINUX
    /* 平台相关代码：Linux的操作文件的OS API */
    int fd = open("./file", O_RDWR | O_CREAT, 0774);
    write(fd, &i, sizeof(i));  //将i写到file中
    printf("linux!!!\n");
#endif

    return 0;
}
