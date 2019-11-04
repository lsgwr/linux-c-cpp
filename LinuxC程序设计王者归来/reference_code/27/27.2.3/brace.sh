#!/bin/sh
# brace.sh 使用双括号计算表达式的值
#在数学表达式中使用加法操作
sum=$((3 + 2)) 
echo $sum
#在数学表达式中使用求余操作
mod=$((3 % 2)) 
echo $mod
#在数学表达式中使用乘法操作
mul=$((3 \* 2))
echo $mul
exit 0
