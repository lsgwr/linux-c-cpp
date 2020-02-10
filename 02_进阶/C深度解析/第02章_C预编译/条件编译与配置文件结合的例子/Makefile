all:
	gcc -o helloworld helloworld.c

Win:
	#执行脚本文件config,传给脚本文件的参数为win
	#脚本会创建config.h,往里面写入#define WINDOWS
	./config.sh win 

Linux:
	#执行脚本文件config,传给脚本文件的参数为linux
	#脚本会创建config.h,往里面写入#define LINUX
	./config.sh linux

clean:
	#执行脚本文件config,传入参数为clean
	#脚本文件会删除可执行文件helloworld和config.h
	 ./config.sh clean 
