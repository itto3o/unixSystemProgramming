#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int X = 100;
int main() {
	pid_t pid;
	int x, n;
	n = 0;
	x = 0;

	pid = fork();

	if(pid < 0) {
		printf("fork fail \n");
		return -1;
	}

	else if(pid == 0) {
		X++;
		x++;
		printf("자식 PID : %d, 부모 PID : %d, X : %d, x : %d\n", (int)getpid(), (int)getppid(), X, x);
	}

	else {
		sleep(5);
		x = 2;
		printf("부모 PID : %d, X : %d, x : %d, pid : %d\n", (int)getpid(), X, x, pid);
	}

	n++;
	printf("n = %d\n", n);
	printf("PID : %d, X : %d, x : %d\n", (int)getpid(), X, x);

	return 0;
}
