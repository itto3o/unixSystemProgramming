#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	if(argc != 2) {
		printf("Usage : %s dirname\n", argv[0]);
		exit(1);
	}

	if(mkdir(argv[1], 0755) == -1) {
		printf("%s mkdir faild\n", argv[1]);
		exit(1);
	}
	else
		printf("%s mkdir successed\n", argv[1]);

	return 0;
}	
