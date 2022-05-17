#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define CHILD_NUM 3

//handler 등록
void handler(int signo) {
	printf("child process exit, pid : %d\n", (int)getpid());
	psignal(signo, "Received Signal");
}

int main(int argc, char* argv[]) {
	pid_t pid[CHILD_NUM];
	//fork 횟수 측정 count
	int count = 0;

	pid[count] = fork();
	if(pid[count] == -1) {
		perror("fork failed");
		exit(1);
	}
	//child
	else if(pid[count] == 0) {
		//본인의 pid 출력,
		printf("%d process wait Ctrl+C...\n", (int)getpid());
		//sigint signal 핸들러 등록
		signal(SIGINT, handler);
		pause();
	}
	else {
		//부모인 경우 fork 한번 더, count++ 
		pid[++count] = fork();
		if(pid[count] == -1) {
			perror("fork failed");
			exit(1);
		}
		//위와 같이 signal 핸들러 등록
		else if(pid[count] == 0) {
			printf("%d process wait Ctrl+C...\n", (int)getpid());
			signal(SIGINT, handler);
			pause();
		}
		else {
			//부모는 한 번 더 fork
			pid[++count] = fork();
			if(pid[count] == -1) {
				perror("fork failed");
				exit(1);
			}
			else if(pid[count] == 0) {
				printf("%d process wait Ctrl+C...\n", (int)getpid());
				signal(SIGINT, handler);
				pause();
			}
			else {
				//최종 부모는 3초 후에 모든 자식프로세스에 SIGINT
				sleep(3);
				for(int i = 0; i < CHILD_NUM; i++)
					kill(pid[i], SIGINT);
			}
		}
	}

	return 0;
}
