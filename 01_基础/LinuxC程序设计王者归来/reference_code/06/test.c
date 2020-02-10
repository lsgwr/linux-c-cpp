int main(void)
{
	struct stat stat_buf; /* 存储文件状态信息 */
	
	if(stat("sl", &stat_buf) == -1){
		perror("fail to stat");
		exit(1);
	}
	
	printf("permission : %d\n", stat_buf.st_mode);
	printf("inode number : %d\n", stat_buf.st_ino);
	printf("device number : %d\n", stat_buf.st_dev);
	printf("r-device number : %d\n", stat_buf.st_rdev);
	printf("link : %d\n", stat_buf.st_nlink);
	printf("uid : %d\n", stat_buf.st_uid);
	printf("gid : %d\n", stat_buf.st_gid);
	printf("file size : %d\n", stat_buf.st_size);
	printf("access time : %d\n", stat_buf.st_atime);
	printf("motify time : %d\n", stat_buf.st_mtime);
	printf("change time : %d\n", stat_buf.st_ctime);
	printf("stat_buf size : %d\n", stat_buf.st_blksize);
	printf("block size : %d\n", stat_buf.st_blocks);

	return 0;
}
