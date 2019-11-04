#!/bin/sh
#shift.sh访问第10个以后的命令行参数
#输出所有的10个命令行参数，每个参数使用位置变量表示
echo No.0 $0
echo No.1 $1
echo No.2 $2
echo No.3 $3
echo No.4 $4
echo No.5 $5
echo No.6 $6
echo No.7 $7
echo No.8 $8
echo No.9 $9
shift 	#移位操作，将第11个命令行参数（$10）移动到$9的位置，$1就丢失了
echo No.0 $0
echo No.1 $1
echo No.2 $2
echo No.3 $3
echo No.4 $4
echo No.5 $5
echo No.6 $6
echo No.7 $7
echo No.8 $8
echo No.9 $9
