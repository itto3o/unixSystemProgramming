#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	char exec[BUFSIZ];

	setuid(0);
	setgid(0);

	sprintf(exec, "%s 2>/dev/null", argv[1]);
	system(exec);

	return 0;
}
