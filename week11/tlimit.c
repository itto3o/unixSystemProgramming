#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

//자녀 pid를 얻어옴
int child_pid;

//alarm시그널을 받으면 자식 프로세스에 sigint
void alrmSig(int signo) {
	kill(child_pid, SIGINT);
}

int main(int argc, char* argv[]) {
	//argc가 3이 아니면 usage출력 후 종료
	if(argc != 3) {
		printf("Usage : %s limit path/program\n", argv[0]);
		return -1;
	}

	int limit = atoi(argv[1]);

	pid_t pid = fork();

	if(pid == -1) {
		perror("fork failed");
		exit(1);
	}
	else if(pid == 0) {
		child_pid = (int)getpid();
		if(execlp("/bin/sh", "sh",  "-c", argv[2], (char*)NULL) == -1) {
			perror("execlp");
			exit(1);
		}
	}
	else {
		signal(SIGALRM, alrmSig);

		alarm(limit);
		pause();
		exit(0);
	}

	return 0;
}
