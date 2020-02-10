#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX 4096
#define STANDARD 0
#define SHORT 1
#define LONG 2
extern int  search(char *path,char *name);
extern int get_load_avg();
