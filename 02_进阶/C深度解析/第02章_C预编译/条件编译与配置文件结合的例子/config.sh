#!/bin/sh -e

#如果config.h文件之前就存在,就使用原来的文件
touch config.h

#清空文件内容
:>config.h


#将pragma once输入config.h,防止头文件重复包含
# >: 会覆盖以前的内容
echo "#pragma once" > config.h


#如果脚本文件参数为win,将#define WINDOWS追加到configh中,>>为追加
if [ "$1" = "win" ] ; then

echo "#define WINDOWS" >> config.h

fi

#如果脚本文件参数为linux,将#define LINUX追加config.h
if [ "$1" = "linux" ] ; then

echo "#define LINUX" >> config.h

fi
