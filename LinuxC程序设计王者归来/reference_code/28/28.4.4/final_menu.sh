#!/bin/sh
# final_menu.sh 使用break语句和死循环实现一个可以多次接收输入的菜单
echo "1 save" 
echo "2 load" 
echo "3 exit" 
echo 	# 输出一个换行
# 接收用户输入的内容 
echo "please choose" 
read chioce
# 使用while循环结构实现多次接收用户的输入
# 快捷键如下
# s——存储（save）
# l——加载（load）
# e——退出（exit）
# 循环结构，当用户输入的不是3、E和e的时候进行循环
while true
do
	case $chioce in 
		1 | S | s)
			echo "save";; 
		2 | L | l)
			echo "load";;  
		3 | E | e) # 输入退出命令时使用break语句跳出循环
			echo "exit"
			break;;
		*) # 其他的输入情况
			echo "invalid choice";;
	esac 
	# 再次接收用户的输入
	echo "please choose"
	read chioce
done
echo "done"
exit 0
