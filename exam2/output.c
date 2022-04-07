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
	int age;
	char name[10];
	
	int i = 0;
	while((n = fscanf(fp, "%s %d", name, &age)) != EOF) {
		printf("%s\t%d\n", name, age);
		i++;
	}

	fclose(fp);
}
