#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUF_SIZE 1024
int main(int argc, char* argv[]) {
	int fd;
	int n = 0;
	char buf[BUF_SIZE];

	fd = open(argv[1], O_RDONLY);
	if(fd == -1) {
		printf("파일이 존재하지 않습니다.\n");
	}

	while((read(fd, buf, 8) > 0))
		n += 8;


	printf("bytes : %d\n", n);

	close(fd);
	return 0;
}
