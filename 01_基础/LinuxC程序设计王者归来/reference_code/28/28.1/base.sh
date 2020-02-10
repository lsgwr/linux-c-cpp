#!/bin/sh
# base.sh 取得shell脚本的文件名
# 使用basename命令得到文件路径的最后一部分，就是shell脚本的文件名
file=`basename $0`
echo "file name : $file"
# 使用pwd命令得到当前路径
path=`pwd`
#将两个字符串连接起来，得到一个完整的shell脚本的文件路径
$((path=$path+$file))
echo "full path : $path"
exit 0
