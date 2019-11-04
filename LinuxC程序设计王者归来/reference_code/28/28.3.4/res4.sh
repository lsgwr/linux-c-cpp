#!/bin/bash
# res4.sh 了解条件是如何判断的
echo "Testing No.9"
if [ "false" ]				#  测试"false"字符串 
then
	echo "false is true."	# 字符串的测试结果为“真”
else
	echo " false is false."
fi
echo 						# 输出一个换行
echo "Testing No.10"
if [ $false ] 				# 测试名字为false的变量
then
	echo "\$false is true."
else
	echo "\$false is false."
fi
exit 0
