all : server client 

server : server.c iolib.c          	 #添加了对iolib.c文件的依赖
	gcc server.c iolib.c -o server  
client : client.c iolib.c
	gcc client.c iolib.c -o client

clean: 
	rm *.o server client

.PHONY: clean
