#!/bin/sh 
# until_add.sh 使用until结构计算1～5的整数的和
i=1
# 条件判断命令表示的是循环结束的条件
until [ $i -gt 5 ] 
do 
	sum=`expr $sum + $i` # 累加和
	echo $sum 
	i=`expr $i + 1` 
done 
echo "done the sum : $sum"
exit 0
