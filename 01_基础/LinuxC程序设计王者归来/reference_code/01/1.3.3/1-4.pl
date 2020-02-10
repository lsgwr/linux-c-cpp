#打开字典文件
open(File,"<dict.txt");
#初始化哈希变量
%hashDict=();
#循环读入文件一行至文件末尾
while($Line=<File>)
{
	#去掉换行字符
	chomp($Line);
	#以”=>”作为分隔符将单词与其翻译进行分割
	($Word,$Trans)=split("=>",$Line);
	#构建哈希表
	$hashDict{$Word}=$Trans;	
}
#关闭文件
close(File);
	#在控制台上输出提示
	#且当用户输入字符为q时退出程序
print "Please Input word you want to search（\"q\" to Exit）:\n";	
while($ForSearch=<stdin>)
{	
	#去掉用户从控制台输入的换行符
	chomp($ForSearch);
	if ( $ForSearch eq "q")
	{
		last;
	}
	#如果在哈希表中找到用户输入的字符串时，输出单词译义
	if ( defined $hashDict{$ForSearch} )
	{
		print "$hashDict{$ForSearch}\n";
	}
	#如果没找到，则输出相应提示语
	else
	{
		print "$For Search is not in the dict!\n";
	}
print "Please Input word you want to search（\"q\" to Exit）:\n";
}
