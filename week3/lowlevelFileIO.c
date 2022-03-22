#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAX_BUF 1024
int main(int argc, char* argv[]) {
	int rfd, wfd, n;
	char buf[MAX_BUF];

	if(argc != 3) {
		printf("Usage : %s source destination\n", argv[0]);
	}
	rfd = open(argv[1], O_RDONLY);
	if(rfd == -1) {
		printf("Open %s", argv[1]);
		exit(1);
	}

	wfd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(wfd == -1) {
		printf("Open %s", argv[2]);
		exit(1);
	}

	while ((n = read(rfd, buf, 8)) > 0)
		if(write(wfd, buf, n) != n) perror("write");

	if (n == -1) perror("Read");

	close(rfd);
	close(wfd);

	return 0;
}
