# 第2章 Vim简介

## 2.1 Vim介绍及Vimrc

### Vim介绍
> Vim = Vi Improved

功能
+ 多级撤销
+ 语法加亮和自动补全
+ 支持多种插件
+ 通过网络协议(HTTP/SSH)编辑文件
+ 多文件编辑
+ 可以编辑压缩格式的文件

### Vimrc
> Vim run command

+ 系统级vimrc(`$VIM/vimrc`)和用户级vimrc(`~/.vim/vimrc`或者`~/.vimrc`)
+ 每一行作为一个命令执行,在打开vim的时候都会先执行，从而实现vim自定义配置

超级好用的配置

+ `set ruler`:最下方实时显示当前光标所在行列
+ `set number`:显示行号
+ `set hlsearch`:高亮显示搜索结果
+ `set incsearch`：边搜索边高亮
+ `set showcmd`:输入命令时自动提示
