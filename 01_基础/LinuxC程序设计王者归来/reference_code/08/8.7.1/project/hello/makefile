hello: hello.o	# 生成hello
	gcc hello.o -o hello
hello.o: hello.c	# 生成hello.o
	gcc -c hello.c
clean:
	rm -rf hello *.o
.PHONY: clean
