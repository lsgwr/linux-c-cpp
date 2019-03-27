#include <stdio.h>
#include <unistd.h>


int main(void)
{
	int ret = 0;	

	char buf[30] = {0};

#if 0	
	close(0);	
	
	ret = scanf("%s", buf);
	//ret = read(0, (void *)buf, 30);
	if(-1 == ret)
	{
		perror("scanf fail");
		//perror("read fail");
		return -1;
	}


	printf("buf = %s\n", buf);	
	
	int num = 0;
	
	num = (buf[0] - '0')*100 + (buf[1] - '0')*10 + (buf[2] - '0');
	
	printf("%d\n", num);
	
#endif

#if 1
	
	//write(1, "hello world\n", 12);
	
	//close(1);
	//int va = 65;
	//write(1, &va, 4);

	//char buf1[5] = {0};
	//buf1[0] = va/10 + '0';
	//buf1[1] = va%10 + '0';
	//buf1[2] = '\n';
	//write(1, buf1, 3);	

	//printf("buf1 = %s\n", buf);
	
	//write(2, "hello world\n", 12);
	
	close(STDERR_FILENO);	
	perror("fail");

#endif 
	




        return 0;
}


