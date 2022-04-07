#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
	FILE *rfp1, *rfp2, *wfp;
	

	rfp1 = fopen(argv[1], "r");
	rfp2 = fopen(argv[2], "r");

	wfp = fopen("hello_new.txt", "w");

	int n = 0;
	while((n = fgetc(rfp1) > 0)){
			fputc(n, wfp);
		}
	while((n = fgetc(rfp2) > 0)) {
		fputc(n, wfp);
	}
	fclose(rfp1);
	fclose(rfp2);
	fclose(wfp);
	
	return 0;
}
