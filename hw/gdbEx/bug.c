#include <stdio.h>
#include <string.h>

int main() {
	int i;
	double j;
	char bug[100] = "";

	for(i = 0; i < 5; i++) {
		j = i/2.0 + i;
		printf("J is %lf\n", j);
	}

	strcpy(bug, "hi");
	printf("bug is %s\n", bug);
	return 0;
}
