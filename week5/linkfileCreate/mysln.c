#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	if(argc != 3) {
		perror("Usage : ./myln file linkfile");
		exit(1);
	}

	struct stat buf;
	struct stat linkBuf;

	stat(argv[1], &buf);
	printf("Before %s Link Count = %d, Inode = %d\n", argv[1], (int)buf.st_nlink, (int)buf.st_ino);

	symlink(argv[1], argv[2]);

	stat(argv[1], &buf);
	lstat(argv[2], &linkBuf);
	printf("After %s Link Count = %d, Inode = %d\n", argv[1], (int)buf.st_nlink, (int)buf.st_ino);
	printf("After %s Link Count = %d, Inode = %d\n", argv[2], (int)linkBuf.st_nlink, (int)linkBuf.st_ino);

	return 0;
}
