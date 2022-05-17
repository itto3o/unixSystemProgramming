#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define CHILD_NUM 3 
void handler(int signo) {
	printf("pid %d process exit\n", (int)getpid());
	exit(0);
}

int main(int argc, char* argv[]) {
	pid_t pid[CHILD_NUM];
	signal(SIGINT, handler);

	for(int i = 0; i < CHILD_NUM; i++) {
		pid[i] = fork();

		if(pid[i] == -1) {
			perror("fork failed");
			exit(1);
		}
		else if(pid[i] == 0) { // child 	
			if(execlp("/bin/sh", "sh", "-c", "./kill", (char*)NULL) == -1) {
				perror("execlp error");
				exit(0);
			}
		}
		else {
			sleep(3);
			for(int i = 0; i < CHILD_NUM; i++)
				kill(pid[i], SIGINT);
			exit(0);
		}
	}	
	return 0;
}
