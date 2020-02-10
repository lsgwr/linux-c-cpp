#!/bin/sh
# menu.sh 使用case结构语句实现一个与用户交互的菜单
echo "1 save" 
echo "2 load" 
echo "3 exit" 
echo 	# 输出一个换行
# 接收用户输入的内容 
echo "please choose" 
read chioce
# 使用case语句实现一个分支结构，处理每一种输入
case $chioce in 
	1)
		echo "save";; 
	2)
		echo "load";; 
	3)
		echo "exit";; 
	*) # 其他的输入情况
		echo "invalid choice"
		exit 1;;
esac 
exit 0
