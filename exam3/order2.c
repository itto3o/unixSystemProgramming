#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int signo) {
	if(execlp("/bin/sh", "sh", "-c", "./cook", (char*)NULL) == -1) {
		perror("execlp");
		exit(1);
	}
	printf("completed?\n");
	kill(getppid(), SIGUSR1);
}

int main() {
	signal(SIGUSR1, handler);
	printf("Waiting...\n");
	while(1) {
	}
	return 0;
}
