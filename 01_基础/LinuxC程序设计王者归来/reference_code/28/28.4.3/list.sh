#!/bin/sh
# list.sh 判断当前目录下每个文件的类型
# 使用for循环，循环参数列表是使用ls命令的输出结果
for file in `ls` 
do 
	if [ -f $file ]		# 判断普通文件
	then 
		echo "$file is a regular file" 
	elif [ -d $file ]	# 判断目录文件
	then
		echo "$file is a directory" 
	else 				# 判断其他文件
		echo "unknown file type"
	fi 
done 
exit 0
