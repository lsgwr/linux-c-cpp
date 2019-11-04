#!/bin/sh
# func_menu.sh 使用input函数封装用户的输入
input()
{
	case $1 in 
		1 | S | s) # 保存命令
			echo "save";; 
		2 | L | l) # 加载命令
			echo "load";;  
		3 | E | e) # 退出命令
			echo "exit"
			break;;
		*) # 其他的输入情况
			echo "invalid choice";;
	esac
}
echo "1 save" 
echo "2 load" 
echo "3 exit" 
echo 	# 输出一个换行
# 使用while循环结构实现多次接收用户的输入
# 快捷键如下
# s——存储（save）
# l——加载（load）
# e——退出（exit）
# 循环结构，当用户输入的不是3、E和e的时候进行循环
while true
do
	# 接收用户输入的内容 
	echo "please choose"
	read res
	input $res
done
echo "done"
exit 0
