#!/bin/sh
# eq_str.sh 测试两个字符串，根据结果输出提示信息
str1="hello world"
str2="hello world"
if [ "$str1" = "$str2" ] ;then # 判断两个字符串是否相等如果相等则输出提示信息
	echo "they are equal"
fi
exit 0
