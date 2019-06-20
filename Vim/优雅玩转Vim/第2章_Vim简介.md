# 第2章 Vim简介

> 先按照[这个教程](http://www.sylar.top/blog/?p=135)安装好oh-my-zsh和vim8.1 

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
> Vim run command,更多配置见 https://github.com/yangvipguang/vimrc-sample/blob/master/vimrc-sample

+ 系统级vimrc(`$VIM/vimrc`)和用户级vimrc(`~/.vim/vimrc`或者`~/.vimrc`)
+ 每一行作为一个命令执行,在打开vim的时候都会先执行，从而实现vim自定义配置

超级好用的配置

+ `set ruler`:最下方实时显示当前光标所在行列
+ `set number`:显示行号
+ `set hlsearch`:高亮显示搜索结果
+ `set incsearch`：边搜索边高亮
+ `set showcmd`:输入命令时自动提示
+ `set autoindent`:自动缩进
+ `set smartindent`:智能缩进
+ `colorscheme slate`:主题设置，可选的主题有
  + blue
  + darkblue
  + default
  + delek
  + desert
  + elflord
  + evening
  + koehler
  + morning
  + murphy
  + pablo
  + peachpuff
  + ron
  + shine
  + slate
  + torte
  + zellner
+ 设置快速保存
  ```vim
  " change the mapleader from \ to ,
  " NOTE: This has to be set before <leader> is used.
  let mapleader=","

  " Quickly save your file.
  map <leader>w :w!<cr>
  ```

### ~/.vimrc的典型配置

```vim
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"                                 Sample vimrc                                 "
"                                                                              "
"                                 Provided by:                                 "
"                                  DevOps24H                                   "
"                                                                              "
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" Save 1,000 items in history 
" vim的命令历史，可以用上下箭头切换
set history=1000

" Show the line and column number of the cursor position
# 最下方先当前的行列和命令信息
set ruler

" Display the incomplete commands in the bottom right-hand side of your screen.  
set showcmd

" Display completion matches on your status line
set wildmenu

" Show a few lines of context around the cursor
set scrolloff=5

" Highlight search matches
" 高亮显示搜索关键字
set hlsearch

" Enable incremental searching
" 实时高亮显示搜索关键字
set incsearch

" Ignore case when searching
" 忽略大小写
set ignorecase

" Override the 'ignorecase' option if the search pattern contains upper case characters.
set smartcase

" Turn on line numbering
" 显示行号
set number

" Turn on file backups
set backup

" Don't line wrap mid-word.
set lbr

" Copy the indentation from the current line.
" 自动缩进
set autoindent

" Enable smart autoindenting.
set smartindent

" Use spaces instead of tabs
set expandtab

" Enable smart tabs
set smarttab

" Make a tab equal to 4 spaces
set shiftwidth=4
set tabstop=4


" Specifiy a color scheme.
" 主题设置
colorscheme slate

" Tell vim what background you are using
" set bg=light
" set bg=dark

" Map Y to act like D and C, i.e. yank until EOL, rather than act like yy
" map Y y$

" Remap VIM 0 to first non-blank character
" map 0 ^

" Easily create HTML unorded lists. 
map <F3> i<ul><CR><Space><Space><li></li><CR><Esc>I</ul><Esc>kcit
map <F4> <Esc>o<li></li><Esc>cit

" change the mapleader from \ to ,
" NOTE: This has to be set before <leader> is used.
let mapleader=","

" Quickly save your file.
map <leader>w :w!<cr>

" For more options see ":help option-list" and ":options".
```

## 2.2 Vim的四种模式

+ 普通模式：打开默认就是
+ 可视：v进入，可以对一整块区域进行操作
+ 插入：insert或i,添加文本
+ 命令：esc进入，和普通模式类似
