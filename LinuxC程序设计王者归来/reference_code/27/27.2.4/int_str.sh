#!/bin/bash
# int_str.sh 演示整型变量和字符串变量之间的微妙差别
a=1024			#整型变量a，将其赋值为1024
((a=$a+1))			#累增变量a的值
echo " the value of a is :$a"
b=102a			#在整型数据中混杂一个字母，把变量b从整型变为字符串
echo " the value of b is :$b"
declare -i b	#使用declare命令，明确指定变量b是一个整型变量
echo " the value of b is :$b"
((b=$b+1))			#累增变量b的值
echo " the value of b is :$b"
c=""		#c变量的值是一个空值
echo " the value of c is :$c"
((c=$c+1))		#使用加法运算符操作一个值为空的变量
echo " the value of c is :$c"
((d=$d+1))		#使用加法运算符操作没有声明的变量
echo " the value of d is :$d"
exit 0
