#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


void handler(int signo) {
	printf("pid %d process exit\n", (int)getpid());
	exit(0);
}

int main(int argc, char* argv[]) {
	signal(SIGINT, handler);
	printf("%d process wait Ctrl+C...\n", (int)getpid());
	pause();
	return 0;
}
