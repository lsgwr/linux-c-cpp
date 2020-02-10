#!/bin/sh
#str.sh 演示测试字符串的方法
str1="hello"
str2="hello"
str3=""	#str3是一个空串
#测试字符串str1和str2相等
test "$str1"="$str2"
echo $?
#测试字符串str3是空串
test -z "$str3"
echo $?
#测试字符串str2是非空串
test -n "$str2"
echo $?
#测试字符串str1和str2不相等
test "$str1"!="$str2"
echo $?
echo "using [ ]"		#使用“[ ]”进行数据测试
#测试字符串str1和str2相等
[ "$str1"="$str2" ]
echo $?
#测试字符串str3是空串
[ -z "$str3" ]
echo $?
#测试字符串str2是非空串
[ -n "$str2" ]
echo $?
#测试字符串str1和str2不相等
[ "$str1"!="$str2" ]
echo $?
exit 0
