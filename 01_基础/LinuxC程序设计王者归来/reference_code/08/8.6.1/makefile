comma :=, 
empty :=
space:= $(empty) $(empty)						# 一个变量
var:= a b c 
bar :=
all:
	bar:= $(subst $(space),$(comma),$(var))	# 调用一个函数
.PHONY: all
