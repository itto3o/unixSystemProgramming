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
	int child_pid[CHILD_NUM];
	//원래는 pid[i] 배열로 선언했는데 자식의자식의자식이 생성되길래 흠..
	//그래서 일단 없애봤는데 다른 부분에서(execlp가 잘 안돼서)
	//잘 안돼서 그냥 냅둠
	pid_t pid;
	signal(SIGINT, handler);

	for(int i = 0; i < CHILD_NUM; i++) {
		pid = fork();

		if(pid == -1) {
			perror("fork failed");
			exit(1);
		}
		else if(pid == 0) { // child 	
			if(execlp("/bin/sh", "sh", "-c", "./kill", (char*)NULL) == -1) {
				perror("execlp error");
				exit(0);
			}
		}
		else {
			sleep(3);
			for(int i = 0; i < CHILD_NUM; i++)
				kill(pid, SIGINT);
			exit(0);
		}
	}	
	return 0;
}
