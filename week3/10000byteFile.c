#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#define BUF_SIZE 5
int main(int argc, char* argv[]) {
	int fd, n;

	fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(fd == -1)
		perror("파일명이 잘못되었습니다.");

	//이렇게 해도 되는 걸까..
	lseek(fd, 10000-1, SEEK_SET);
	write(fd, "\0", 1);

	close(fd);
	return 0;
}
