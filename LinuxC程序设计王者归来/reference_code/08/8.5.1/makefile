var1 =					#这里是一个空值
var2 = hello
all:
ifdef $var1				#判断var1变量是否定义
	@echo "var1 is defined"
else
	@echo "var1 is undefined"
endif
ifeq ($var1,$var2)	# 判断var1和var2的值
	@echo "they are equal"
else
	@echo "they are not equal"
endif
.PHONY: all
