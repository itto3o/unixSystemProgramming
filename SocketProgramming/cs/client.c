#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

//server와 동일한 포트 넘버
#define PORTNUM 9002

int main(void) {
	char buf[256];
	//sever의 정보를 저장할 구조체 선언
	struct sockaddr_in sin;
	int sd;

	//sin에 포트넘버, 서버의 ip주소를 담는다
	//이때 ip주소는 localhost
	memset((char*)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	//socket 생성, TCP로 만들기
	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	//sd에 sin의 서버 정보로 socket connection
	if(connect(sd, (struct sockaddr *)&sin, sizeof(sin))) {
		perror("connect");
		exit(1);
	}

	//보낼 메시지 입력
	printf(">> ");
	fgets(buf, 256, stdin);

	//입력 후 send
	if(send(sd, buf, sizeof(buf)+1, 0) == -1) {
		perror("send");
		exit(1);
	}

	//서버의 응답을 받아오기
	if(recv(sd, buf, sizeof(buf), 0) == -1) {
		perror("recv");
		exit(1);
	}

	//서버 응답 출력
	printf("** From Server : %s\n", buf);

	close(sd);
	
}
