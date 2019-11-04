#!/bin/bash
# res1.sh 了解条件是如何判断的
echo "Testing No.1"
if [ 0 ]	 #  测试值0
then
	echo "0 is true."
else
	echo "0 is false."
fi
echo 		# 输出一个换行
echo "Testing No.2"
if [ 1 ]	# 测试值1
then
	echo "1 is true."
else
	echo "1 is false."
fi
echo 		# 输出一个换行
echo "Testing No.3"
if [ -1 ]	# 测试值-1
then
	echo "-1 is true."
else
	echo "-1 is false."
fi
exit 0
