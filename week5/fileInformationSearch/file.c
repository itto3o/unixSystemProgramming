#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	
	if(argc == 1) {
		perror("Add file name");
		exit(1);
	}

	struct stat buf;
	stat(argv[1], &buf);

	printf("Mode = %o (16진수: %x)\n", (unsigned int)buf.st_mode, (unsigned int)buf.st_mode);

	if(S_ISDIR(buf.st_mode))
		printf("%s : Directory\n", argv[1]);

	if(S_ISREG(buf.st_mode))
		printf("%s : Regular File\n", argv[1]);

	if(S_ISFIFO(buf.st_mode))
		printf("%s : FIFO\n", argv[1]);
	
	if(S_ISLNK(buf.st_mode))
		printf("%s : Symbolic File\n", argv[1]);

	return 0;	
}
