#!/bin/sh
# fast_menu.sh 使用case结构语句实现一个与用户交互的菜单，添加了快捷键
echo "1 save" 
echo "2 load" 
echo "3 exit" 
echo 	# 输出一个换行
# 接收用户输入的内容 
echo "please choose" 
read chioce
# 使用case语句实现一个分支结构，处理每一种输入
# 快捷键如下
# s——存储（save）
# l——加载（load）
# e——退出（exit）
case $chioce in 
	1 | S | s)
		echo "save";; 
	2 | L | l)
		echo "load";; 
	3 | E | e)
		echo "exit";; 
	*) # 其他的输入情况
		echo "invalid choice"
		exit 1;;
esac 
exit 0
