#!/bin/sh
# and.sh 检查两个文件是否同时可写
[ -w $1 -a $0 ] #检查两个文件是否同时可写，其中一个是shell脚本本身
echo $?
exit 0
