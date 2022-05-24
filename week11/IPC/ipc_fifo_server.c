#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

//handler에서 사용할 수 있도록 전역변수로 선언
int pd_s, pd_c, n;
char exit_msg[] = "exit\0";

void handler(int signo) {
	//exit를 print하고
	printf("FIFO exit\n");

	//fifo를 통해 exit 메시지를 client에 전달
	n = write(pd_s, exit_msg, strlen(exit_msg)+1);
	if(n == -1) {
		perror("write H-FIFO");
		exit(1);
	}	
	//종료
	exit(0);
}

int main(int argc, char* argv[]) {
	char msg[80];
	char inmsg[80];
	printf("Server =====\n");

	//^C가 입력되면 handler 실행
	signal(SIGINT, handler);

	//HAN-FIFO로 서버에서 클라이언트에 메시지 보내기
	if(mkfifo("./HAN-FIFO", 0666) == -1) {
		perror("mkfifo");
		exit(1);
	}

	//C-FIFO로 클라이언트에서 메시지 받아오기
	if(mkfifo("./C-FIFO", 0666) == -1) {
		perror("mkfifo C-FIFO");
		exit(1);
	}

	//fork
	pid_t pid;
	pid = fork();

	if(pid == -1) {
		perror("fork failed");
		exit(1);
	}
	else if(pid == 0) { //자식프로세스, C-FIFO에서 읽어오기만 수행
		if((pd_c = open("./C-FIFO", O_RDONLY)) == -1) {
			perror("open C-FIFO");
			exit(1);
		}	

		//무한 반복 하면서
		while(1) {
			//계속 읽어오기
			while((n = read(pd_c, inmsg, 80)) > 0) {
				//만약 exit 메시지가 왔다면 부모 프로세스 종료 후 break
				if(strcmp(inmsg, exit_msg) == 0) {
					kill((int)getppid(), SIGINT);
				//	kill((int)getpid(), SIGINT);
					break;
				}

				//그게 아니라면
				else {
					//client에서 읽어온 메시지를 출력
					write(1, "\nFrom Client :", 14);
					write(1, inmsg, n);
					if(n == -1) {
						perror("read C-FIFO");
						exit(1);
					}
					write(1, "\n", 1);
				}
			}
		}

	}
	else {//부모 프로세스, HAN-FIFO에 쓰기만 수행
		if((pd_s = open("./HAN-FIFO", O_WRONLY)) == -1) {
			perror("open");
			exit(1);
		}

		//무한 반복하면서 입력 기다리기
		while(1) {
			scanf("%s", msg);
		
			//받은 입력을 HAN-FIFO에 write
			n = write(pd_s, msg, strlen(msg)+1);
			if(n == -1) {
				perror("write H-FIFO");
				exit(1);
			}	
		}

	}

	close(pd_s);
	close(pd_c);

	return 0;
}
