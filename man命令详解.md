# man命令详解

> Linux系统提供了相对比较丰富的帮助手册（man），man是manual的缩写，在日常linux系统管理中经常用到，今天就简单聊聊man。man 本身也提供自己的帮助手册，通过man就可以查看

## （1）man手册分为多个section，每个section用一个字符表示。

这里的section可以理解为类别，例如：man 1 passwd 和 man 5 passwd是不一样的类别（详细见表一）。通常我们使用man passwd，这个时候man就按照预先设置的搜索路径和顺序去搜索passwd，当搜索到一个就停止继续搜索并将结果显示出来，如果我们指定了section，那么man只会在指定的section里去查找man帮助页  

| section | 名称      | 说明          |
| ------- | ------- | ----------- |
| 1       | 用户命令    | 用户可以操作的指令   |
| 2       | 系统调用    | 内核提供的函数     |
| 3       | C库函数    | 常用的函数库      |
| 4       | 设备和特殊文件 | 通常是/dev下的文件 |
| 5       | 文件格式和约定 | 对一些文件进行解释   |
| 6       | 游戏      |             |
| 7       | 杂项      | 例如宏命令包、协定   |
| 8       | 系统管理工具  | 通常只有管理员可以使用 |


## （2）man的配置文件

man的配置文件是`/etc/man.config`，我们现学现用，可以通过`man 5 man.config`看看这个配置文件的帮助信息

对于man.config，我们日常使用的不多，一般都是默认的设置，比较重要的是MANPATH(man帮助文件存放的路径)和MANSECT(man搜索的顺序)两个参数，通常不建议修改。

## （3）man的日常使用。

### man常用操作

> 使用man打开帮助手册，里面很多操作与我们经常使用的vi编辑器类似，当然可以通过h键查看具体的帮助信息，下面只简单谈谈我们经常使用的一些操作

+ 上下翻页。最常用的是使用空格键向下翻页。另外，[Page Up] 可以向上翻页，[Page Down]也可以实现向下翻页，[Home]返回首页，[End]返回末页。
+ 行移动。使用键盘方向键进行上下文移动，或者使用j键往下移动， k键向上移动。
+ 查找。使用/string向下搜索string关键字，?string向上搜索string关键字。n键继续关键字的下一个搜索，N键反向搜索关键字。
+ 书签。man中可以定义书签，当我们想把帮助页的某个位置记录下来以便后面查看，就可以定义个书签。例如在当前位置定义个书签letter，我们需要输入m键后，再输入定义的书签名letter即可。那么如何使用这个书签呢？在当前帮助页里输入单引号'letter就可以定位到书签的位置。
+ 执行shell。在man页内可以执行shell，通过!号再输入shell即可执行。例如：!echo 'hello world'，即可打印hello world。这个在日常工作中基本用不到，这里提出来也就想开阔下大家的思路。
+ 退出。q键退出当前帮助手册。

### man常用命令参数

+ `man -a`：搜索并打开所有man中同名帮助 
  例如 `man passwd`, 你首先会进入一个`PASSWD(1) section`用户命令类的帮助手册，你再按q键退出当前正在显示的帮助手册，就会进入`PASSWD(5) section`文件格式类的帮助手册
  
+ `man -aw`：显示所有手册文件的路径。例如`man -aw passwd`,显示如下：
  
  ```shell
  /usr/share/man/man1/passwd.1.gz 
  /usr/share/man/man5/passwd.5.gz 
  ```
  
+ `man -M`：指定手册文件的搜索路径
  有的时候我们自己安装的软件是带有自己的帮助文件的，通常不在我们的MANPATH 里面，那么我们就可以手动指定man搜索的文件路径  
  如 `man -M /home/mysql/man mysql` 显示的就是你安装的mysql的帮助，而不是系统默认的旧版mysql的帮助  
  
+ `man -k`：根据关键字搜索联机帮助，是一种模糊搜索
  例如要查找"passwd"相关的信息，使用`man -k passwd`会找到很多和passwd相关的帮助页
  
+ `man -f`：关键字精确搜索，与-k不同，它只搜索与关键字完全匹配的帮助页

## 编辑推荐

+ [su 中文man页面](http://os.51cto.com/art/201109/291198.htm)
+ [wget 中文man页面](http://os.51cto.com/art/201109/291204.htm)
+ [curl 中文man页面](http://os.51cto.com/art/201109/291206.htm)
+ [find 中文man页面](http://os.51cto.com/art/201109/293912.htm)
+ [sort 中文man页面](http://os.51cto.com/art/201110/298327.htm)
+ [gcc 中文man页面](http://os.51cto.com/art/201110/298339.htm)
