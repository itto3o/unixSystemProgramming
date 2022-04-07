#include <stdio.h>
#include <stdlib.h>
#include "info.h"

int main(int argc, char* argv[]) {
	FILE* fp;
	fp = fopen(argv[1], "wb");
	if(argc != 2) {
		perror("Usage : .bin\n");
		exit(1);
	}

	int number = 0;

	printf("몇 명의 정보를 담는가?\n");
	scanf("%d", &number);

	struct info info[number];

	for(int i = 0; i < number; i++) {
		printf("이름과 나이?(0%d)", i+1);
		scanf("%s %d", info[i].name, &(info[i].age));
		//fprintf(fp, "%s\t%d", info[i].name, info[i].age);
		fwrite(&info[i], sizeof(info[i]), 1, fp);
	}
	
	fclose(fp);
}
