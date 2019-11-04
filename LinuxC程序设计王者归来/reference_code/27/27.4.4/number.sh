#!/bin/sh
# number.sh 演示测试两个数据
#测试两个数据相等
test "1" -eq "2"
echo $?
#测试两个数据不相等
test "1" -ne "2"
echo $?
#测试比较两个数据的大小
test "1" -gt "2"
echo $?
test "1" -lt "2"
echo $?
#测试两个数据的大小，包括等于
test "2" -ge "2"
echo $?
test "2" -le "2"
echo $?
echo "using [ ]"		#使用“[ ]”进行数据测试
#测试两个数据相等
[ "1" -eq "2" ]
echo $?
#测试两个数据不相等
[ "1" -ne "2" ]
echo $?
#测试比较两个数据的大小
[ "1" -gt "2" ]
echo $?
[ "1" -lt "2" ]
echo $?
#测试两个数据的大小，包括等于
[ "2" -ge "2" ]
echo $?
[ "2" -le "2" ]
echo $?
exit 0
