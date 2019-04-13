#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char const *argv[])
{
    int skfd;
    skfd = socket(AF_INET, SOCK_STREAM, 0);
    return 0;
}
