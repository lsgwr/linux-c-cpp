#!/bin/sh 
# add.sh计算1～5的和
i=1 # 循环因子
# 当i小于等于5的时候执行循环体中的命令
while [ $i -le 5 ] 
do 
	sum=`expr $sum + $i` 
	echo $sum
	i=`expr $i + 1` 
done 
echo "done the sum : $sum"
exit 0 
