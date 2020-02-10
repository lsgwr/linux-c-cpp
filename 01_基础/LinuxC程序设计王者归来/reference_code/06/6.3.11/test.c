int main(void)
{
	struct stat buf; /* 存储文件状态信息 */
	if(stat("sl", &buf) == -1){
		perror("fail to stat");
		exit(1);
	}
	printf("permission : %d\n", buf.st_mode);
	printf("inode number : %d\n", buf.st_ino);
	printf("device number : %d\n", buf.st_dev);
	printf("r-device number : %d\n", buf.st_rdev);
	printf("link : %d\n", buf.st_nlink);
	printf("uid : %d\n", buf.st_uid);
	printf("gid : %d\n", buf.st_gid);
	printf("file size : %d\n", buf.st_size);
	printf("access time : %d\n", buf.st_atime);
	printf("motify time : %d\n", buf.st_mtime);
	printf("change time : %d\n", buf.st_ctime);
	printf("buf size : %d\n", buf.st_blksize);
	printf("block size : %d\n", buf.st_blocks);
	return 0;
}
