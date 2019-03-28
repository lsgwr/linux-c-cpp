13. opendir、readdir
	
		opendir：打开目录，以便调用readdir读取目录项
		
		readdir：读取目录里面的目录项
		
		
		什么是目录项？
			目录里面的数据，其实就是一条一条的目录项，每个目录项就是一个文件的基本信息，包含两个最重要的基本信息，
			
			文件名
			inode节点号
			
			图：
				
			
			
	13.1 opendir
		13.1.1 函数原型
				#include <sys/types.h>
				#include <dirent.h>
				
				DIR *opendir(const char *name);

		（1）功能：打开目录
					不能使用open函数打开目录，只能使用opendir打开。
		
		
		（2）参数：name：需打开目录的路径名

				
		（3）返回值
				· 调用成功：返回一个DIR *的指针，这个指针指向了被打开的目录，readdir通过这个指针就可以读取目录的目录项。
					
				· 调用失败：返回NULL，errno被设置。
			
					
		13.1.2 代码演示
			
			
			
	13.2 readdir
	
		13.2.1函数原型
			#include <dirent.h>
			
			struct dirent *readdir(DIR *dirp);
			
			（1）功能：读取目录里的目录项。
			
					每调用一次，就读取出一条目录项。
						
						
			（2）参数dirp：opendir打开目录时，得到的指针。
						
						
			（3）返回值：调用成功，返回指针指向struct dirent结构体的指针。
			
						man readdir能查看到这个结构体，这个结构体其实是定义在了<dirent.h>头文件中。
						
							这个结构体就是用来存放一条目录项的，调用readdir读取到目录项后，会自动开辟一个struct dirent变量来存放目录项，
						然后将变量的指针返回，应用程序通过这个指针，就可以访问结构体中的目录项信息（文件基本信息）。
						
						struct dirent
						{
									ino_t  					d_ino;      	/* i节点编号 */ 重点
									off_t     			d_off;       	/* 地址偏移 */
									unsigned short 	d_reclen; 		/* 本条目录项的大小 */
									unsigned char  	d_type;   		/* 文件类型，不是所有系统都支持 */
									char  					d_name[256];  /* 文件名字 */ 重点
						};
			
					返回NULL的话有如下两种情况：
						1）读到目录的末尾时，返回NULL。
						
						2）函数调用失败时，也返回NULL，不过errno被设置。	
					
						怎么判断函数是否调用失败了呢，如果ernno==0，表示没有设置错误号，返回NULL是因为读到了文件的末尾。
						如果errno!=0，表示是因为函数调用出错而返回的NULL。
						
			（5）代码演示
	
	13.3 修改my_ls
			
			修改该代码，实现一个功能：当跟的参数是目录时，将目录中所有文件的属性信息全部都显示出来。
			
		（1）实现方法
					判断文件是不是目录
				
					（a）如果不是，直接调用lstat显示属性
					
					（b）如果是目录
					
								1）打开目录
								
								2）获取每一条目录项中的文件名
								
								3）把文件名给lstat，获取属性