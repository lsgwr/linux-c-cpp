#!/bin/sh
#default.sh 设置变量的默认值
echo linux $version 
echo "set default-value"
echo linux ${version:-2.6.12} 	#设置变量的默认值
echo the value is : $version 	#变量本身的值并没有改变
version="new version" 			#将变量赋值
echo linux ${version:-2.6.12}	#再次输出该变量的值
