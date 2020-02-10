#!/bin/sh
# for_add.sh 计算1～5的整数的和
#使用for循环实现累加，循环变量i依次等于循环参数列表中的值
for i in 1 2 3 4 5
do 
	sum=`expr $sum + $i`
	echo "i=$i"
	echo "sum=$sum"
done
echo "done ths sum : $sum"
exit 0
