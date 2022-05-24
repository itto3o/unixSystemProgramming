#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

//handler에서 사용할 수 있도록 전역 변수로 선언
int pd_c, pd_s, n;
char exit_msg[] = "exit\0";

void handler(int signo) {
	//FIFO exit 출력
	printf("FIFO exit\n");

	//C-FIFO에 exit 보내기
	n = write(pd_c, exit_msg, strlen(exit_msg)+1);
	if(n == -1) {
		perror("write C-FIFO");
		exit(1);
	}
	exit(0);
}
int main(int argc, char* argv[]) {
	char inmsg[80];
	char msg[80];

	printf("Client =====\n");

	signal(SIGINT, handler);

	pid_t pid;
	pid = fork();

	if(pid == -1) {
		perror("fork failed");
		exit(1);
	}
	else if(pid == 0) {//자식 프로세스, HAN-FIFO에서 읽어오기만 수행
		if((pd_s = open("./HAN-FIFO", O_RDONLY)) == -1) {
			perror("open");
			exit(1);
		}
	
		while(1) {
			while((n = read(pd_s, inmsg, 80)) > 0) {
				//만약 exit 메시지가 받아와졌다면
				if(strcmp(inmsg, exit_msg) == 0) {
					//SIGINT 신호 보내고 break
					kill((int)getppid(), SIGINT);
					break;
				}

				//그게 아니라면 메시지 출력
				else {
					write(1, "\nFrom Server :", 14);
					write(1, inmsg, n);

					if(n == -1) {
						perror("read");
						exit(1);
					}
					write(1, "\n", 1);
				}
			}
		}
	}
	else { //부모 프로세스는 C-FIFO에 write만
		if((pd_c = open("./C-FIFO", O_WRONLY)) == -1) {
			perror("open C-FIFO");
			exit(1);
		}
	
		//무한 반복하면서 입력 대기
		while(1) {	
			scanf("%s", msg);

			n = write(pd_c, msg, strlen(msg)+1);
			if(n == -1) {
				perror("write C-FIFO");
				exit(1);
			}

		}
	}

	close(pd_s);
	close(pd_c);

	return 0;
}
