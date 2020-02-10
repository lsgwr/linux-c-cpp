#!/bin/sh
# file_test.sh 测试文件的种类
if [  -L $1 ]	# 符号链接
then
	echo "symlink file"
elif [ -d  $1 ]	# 目录文件
then
	echo "dir file"
elif [ -f  $1 ] # 普通文件
then
	echo "regular file"
fi
exit 0
