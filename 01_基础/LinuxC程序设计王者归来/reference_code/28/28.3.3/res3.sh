#!/bin/bash
# res3.sh 了解条件是如何判断的
echo "Testing No.6"
if [ $xyz ]				# 判断一个未初始化的变量
then
	echo "Uninitialized var is true."
else
	echo "Uninitialized var is false."
fi
echo 					# 输出一个换行
echo "Testing No.7"
if [ -n "$xyz" ]		# 判断变量是否是空的条件操作符
then
		#此时xyz的值仍是假的，但是加上-n后这个条件判断的值就是真的了
	echo "Uninitialized var is true." 
else
	echo "Uninitialized var is false."
fi
echo 	# 输出一个换行
xyz=	# 初始化变量xyz，但是其值为空
echo "Testing No.8"
if [ -n "$xyz" ]
then
	echo "Null var is true."
else
	echo "Null var is false."
fi
exit 0
