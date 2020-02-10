#!/bin/sh
#expr.sh 使用expr命令计算表达式的值
#在数学表达式中使用加法操作
expr 3 + 2 
echo $?
#在数学表达式中使用求余操作
expr 3 % 2 
echo $?
#在数学表达式中使用乘法操作时乘法符号必须被转义
expr 3 \* 2 
echo $?
exit 0
