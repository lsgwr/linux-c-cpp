#!/bin/sh
#unset.sh 使用unset清除变量的值
echo "before clearance"
string="hello world"
echo $string	#输出string 变量的原来的值
echo "after clearance"
unset string 
echo $string 	#输出清除了string变量后的值
