CC = xxx-gcc
CFLAGS += xxx 									# 编译选项
LDFLAGS += xxx									# 链接选项
EXEC = xxx										# 生成的可执行文件
all: $(EXEC)
.PHONY all
xxx: xxx.c										# 规则
	$(CC) $(CFLAGS) $(LDFLAGS) xxx.c–o $@		# $@表示目标中需要生成的文件
clean:
	-rm –f  $(EXEC) *.elf *.gdb *.o *.a			# 忽略命令执行的错误，删除所有
												生成的文件
.PHONY: clean

