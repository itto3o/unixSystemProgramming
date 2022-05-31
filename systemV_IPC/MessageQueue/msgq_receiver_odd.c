#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

//받아올 메시지를 저장하는 구조체
struct mymsgbuf {
	long mtype;
	char mtext[80];
};

int main(int argc, char* argv[]) {
	struct mymsgbuf inmsg;
	key_t key;
	int msgid, len;

	//sender에서 받아온 key와 동일한 key를 생성하고
	key = ftok("keyfile", 1);
	//msgqueue 생성
	if((msgid = msgget(key, 0)) < 0) {
		perror("msgget error");
		exit(0);
	}

	//홀수 내용만 msgq에서 받아오고 출력
	len = msgrcv(msgid, &inmsg, 80, 1, 0);
	printf("Received Msg = %s, Len = %d\n", inmsg.mtext, len);

	return 0;
}
