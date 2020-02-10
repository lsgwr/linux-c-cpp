#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int n = 5, i;				
pid_t p, q;

	if(argc == 2){	
		n = atoi(argv[1]);
	}
    q = getpid();

	for(i = 0; i < n; i++)	 {
        p = fork();
		if(p == 0) {
			break;			
        } 
    }

	if(n == i){  // parent
		sleep(n);
		printf("I am parent, pid = %d\n", getpid());
        for (i = 0; i < n; i++) {
            p = waitpid(0, NULL, WNOHANG);
            printf("wait  pid = %d\n", p);
        }
	} else {
		sleep(i);
		printf("I'm %dth child, pid = %d\n", 
				i+1, getpid());
	}
    ///
    //./
    //
    //
    //
    //
    //
    //

	return 0;
}
