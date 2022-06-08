#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

#define PORTNUM 9002

int main(void) {
	char buf[256];
	//서버와 클라이언트의 정보를 담을 구조체 선언
	struct sockaddr_in sin, cli;
	int sd, ns, clientlen = sizeof(cli);

	//socket 생성, TCP로 만들기
	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	//sin에 포트넘버와 ip주소를 담는다.
	//이때 ip 주소는 localhost
	memset((char*)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	//bind해주기
	if(bind(sd, (struct sockaddr *)&sin, sizeof(sin))) {
		perror("bind");
		exit(1);
	}

	//listen으로 클라이언트의 최대 접속 개수를 정하고,
	if(listen(sd, 5)) {
		perror("listen");
		exit(1);
	}

	while(1) {
		//클라이언트의 접속을 대기한다
		//client의 접속 정보를 받아온다
		if((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1) {
			perror("accept");
			exit(1);
		}

		//fork로 서버가 여러개의 요청을 처리할 수 있도록
		switch (fork()) {
			case 0:
				//클라이언트의 요청만 수행하도록 sd는 close
				close(sd);

				//message는 client에서 오는 단방향으로 설계해서 recv먼저
				if(recv(ns, buf, sizeof(buf), 0) == -1) {
					perror("recv");
					exit(1);
				}
				//recv한 client mesg 출력
				printf("** From Client: %s\n", buf);

				//본인의 pid주소를 buf에 저장
				sprintf(buf, "This is a reply from %d.", getpid());
				//strcpy(buf, "Welcome to Server");
				//ns의 client로 보내기
				if(send(ns, buf, strlen(buf) + 1, 0) == -1) {
					perror("send");
					exit(1);
				}
				printf("Repiled.\n");

				usleep(10000);
				exit(0);
		}
		close(ns);
	}
}
