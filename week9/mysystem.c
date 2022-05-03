#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void mysystem(char* argv[]) {
	pid_t pid;

	//fork
	switch(pid = fork()) {
		case -1 : //fork 실패
			perror("fork");
			exit(1);
			break;
		case 0: //child process
			//execl로 sh -c argv 실행, 그냥 argv로 넣으니 쓰레기 값이 함께 들어간다...
			if(execl("/bin/sh", "sh", "-c", argv[1], argv[2], (char*)NULL) == -1) {
				perror("execl");
				exit(1);
			}
			//정상 작동 후 exit
			exit(0);
			break;
		default : //parent process
			wait(NULL);	//child가 다 끝난 후에 return
			return;
			break;
	}

}

int main(int argc, char* argv[]) {
	mysystem(argv);
	return 0;
}
