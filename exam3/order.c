#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



void cookHandler(int signo) {
// sighold(SIGINT);
	if(execlp("/bin/sh", "sh", "-c", "./cook", (char*)NULL) == -1) {
		perror("execlp");
		exit(1);
	}
	printf("completed?\n");
	kill(getppid(), SIGUSR1);
}

void exitHandler(int signo) {
	printf("parent exit\n");
	exit(0);
}
int main(int argc, char* argv[]) {
	sigset_t sig;
	sigemptyset(&sig);
	sigaddset(&sig, SIGINT);

	sigset_t sigUSR;
	sigemptyset(&sigUSR);
	sigaddset(&sigUSR, SIGUSR1);

	signal(SIGINT, exitHandler);

	char answer;
	pid_t pid;

	while(1) {
	switch(pid = fork()) {
		case -1 :
			perror("fork faild");
			exit(1);
			break;
		case 0 :
			signal(SIGUSR1, cookHandler);
			sleep(30);
			break;
		default :
			printf("Start Cook? (y, n)");
			scanf("%c", &answer);

			if(answer == 'y') {
				sigprocmask(SIG_BLOCK, &sig, (sigset_t *)NULL);
				//sighold(SIGINT);
				kill(pid, SIGUSR1);
				sigsuspend(&sigUSR);
				printf("suspend?\n");
				//sigrelse(SIGINT);
				sigprocmask(SIG_UNBLOCK, &sig, (sigset_t *)NULL);
//				kill(pid, SIGINT);
				kill(pid, SIGINT);
//				exit(0);
				continue;
			}
			else if(answer == 'n') {
				kill(pid, SIGINT);
				exit(0);
			}
			break;
	}
	}
	return 0;
}
