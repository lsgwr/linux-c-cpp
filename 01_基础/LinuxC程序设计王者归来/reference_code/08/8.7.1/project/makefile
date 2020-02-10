SUBDIRS := list hello						# 子目录
all : modules
.PHONY:all
modules:
#进入每个文件夹并执行文件夹中的makefile
	for dir in $(SUBDIRS);do make -C $$dir || exit 1;done	 
.PHONY:modules
clean:
#进入每个文件夹并调用makefile中的clean
	for dir in $(SUBDIRS);do make -C $$dir clean;done
.PHONY: clean
