#!/bin/bash
# res2.sh 了解条件是如何判断的
echo "Testing No.4"
if [ ]			#测试空值NULL
then
	echo "NULL is true."
else
	echo "NULL is false."
fi
echo			# 输出一个换行
echo "Testing No.5"
if [ "xyz" ]	# 测试任意一个字符串
then
	echo "string is true."
else
	echo "string is false."
fi
exit 0
