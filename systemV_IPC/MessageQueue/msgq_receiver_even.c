#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

//받아올 메시지를 저장할 구조체
struct mymsgbuf {
	long mtype;
	char mtext[80];
};

int main(int argc, char* argv[]) {
	struct mymsgbuf inmsg;
	key_t key;
	int msgid, len;

	//sender에서 생성한 key와 동일하게 생성
	key = ftok("keyfile", 1);
	//key로 msgq 생성
	if((msgid = msgget(key, 0)) < 0) {
		perror("msgget error");
		exit(0);
	}

	//짝수이므로 메시지 타입이 2인 메시지만 rcv
	len = msgrcv(msgid, &inmsg, 80, 2, 0);
	printf("Received Msg = %s, Len = %d\n", inmsg.mtext, len);

	return 0;
}
