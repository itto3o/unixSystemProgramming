#include <stdio.h>
#include <stdlib.h>
#include "info.h"

int main(int argc, char* argv[]) {
	FILE* fp;
	fp = fopen(argv[1], "rb");
	
	if(argc != 2) {
		perror("Usage : .bin\n");
		exit(1);
	}
	
	printf("Name\tAge\n");
	
	int n;
	struct info infomember;
	
	while((n = fread(&infomember, sizeof(infomember), 1, fp)) > 0) {
		printf("%s\t%d\n", infomember.name, infomember.age);
	}

	fclose(fp);
}
