#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
	FILE *rfp, *wfp1, *wfp2;
	struct stat buf;
	

	rfp = fopen(argv[1], "r");
	stat(argv[1], &buf);

	int end = buf.st_size;
	int half = end/2;

	wfp1 = fopen("hello_01.txt", "w");
	wfp2 = fopen("hello_02.txt", "w");

	printf("%d %d", end, half);

	int n = 0;
	int c = 0;
	while(n < half) {
		c = fgetc(rfp);
		fputc(c, wfp1);
		n++;
	}

	while(n < end) {
		c = fgetc(rfp);
		fputc(c, wfp2);
		n++;
	}

	fclose(rfp);
	fclose(wfp1);
	fclose(wfp2);
	
	return 0;
}
