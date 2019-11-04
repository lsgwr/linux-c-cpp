#!/bin/sh
# ifelse.sh 将两个数由小到大输出
a=4
b=3
if [ $a -gt $b ] #如果变量a大于变量b则交换两个变量
then
	t=$b
	b=$a
	a=$t
fi
echo "a = $a" #输出两个变量
echo "b = $b"
exit 0
