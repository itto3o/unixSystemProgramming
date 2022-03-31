//abcdefghijklmnopqrstuvwxyz를 짝수 인덱스만 출력하기 (또는 파일 만들기)
//lseek, fseek, fread/fwrite 사용해서

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

//1. lseek 사용
void Use_lseek(char* filename) {
	int fd, n;
	char c[BUFSIZ];

	fd = open(filename, O_RDONLY);
	if(fd == -1) {
		perror("open failed");
		exit(1);
	}
	printf("use lseek : ");

	while((n = read(fd, c, 1)) > 0) {
		c[2] = '\0';
		printf("%s", c);
		lseek(fd, 1, SEEK_CUR);
	}
	
	close(fd);
}

//2. fseek 사용
void Use_fseek(char* filename) {
	FILE *fp;
	int c = 0;

	if((fp = fopen(filename, "r")) == NULL) {
		perror("fopen failed");
		exit(1);
	}
	printf("use fseek : ");
	

	while((c = fgetc(fp)) > 0) {
		printf("%c", c);
		fseek(fp, 1, SEEK_CUR);
	}

	fclose(fp);
}

//3. fwrite, fread 사용
void Use_frw(char* filename) {
	FILE *rfp;
	char c[BUFSIZ];
	int n;

	if((rfp = fopen(filename, "r")) == NULL) {
		perror("fopen failed");
		exit(1);
	}
	printf("use fread & fwrite : ");
	
	while((n = fread(c, sizeof(char), 2, rfp)) > 0) {
		c[1] = '\0';
		printf("%s", c);
	}
	
	fclose(rfp);
}
int main(int argc, char* argv[]) {
	Use_lseek(argv[1]);
	Use_fseek(argv[1]);
	Use_frw(argv[1]);
	return 0;
}
