#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int sec = 1;

void handler(int signo) {
	printf("My Message No.%d\n", sec++);
}		

void stopwatch() {
	while(1) {
		alarm(1);
		pause();
	}
}

void main() {
	signal(SIGALRM, handler);

	stopwatch();
}

