14. chmode、fchmod

	14.1 函数原型
			#include <sys/stat.h>

      int chmod(const char *pathname, mode_t mode);
      int fchmod(int fd, mode_t mode);
		
		（1）功能：修改文件权限，比如将权限指定为0664等。
				chmod命令就是调用这两个函数来实现的。
			
				chmod：使用路径名操作
				fchmod：使用文件描述符操作
				

		（2）返回值：成功返回0，失败返回-1，errno被设置、
					
					
	14.2 代码演示	
			chmod("./file.txt", 0644);
