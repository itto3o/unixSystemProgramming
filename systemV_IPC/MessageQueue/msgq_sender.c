#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct mymsgbuf {
	long mtype;
	char mtext[80];
};

int main(int argc, char* argv[]) {
	//인자가 3개가 아니면 usage 출력, 종료
	if(argc != 3) {
		printf("Usage %s mtype msg", argv[0]);
		exit(1);
	}

	key_t key;
	int msgid;
	int mtype;
	struct mymsgbuf mesg;

	//ftok로 key 생성
	key = ftok("keyfile", 1);

	//msgget
	msgid = msgget(key, IPC_CREAT|0644);
	if(msgid == -1) {
		perror("msggmet error");
		exit(1);
	}

	//인자로 받아온 숫자를 atoi로 int형변환
	mtype = atoi(argv[1]);

	//짝수면 mtype을 2, 홀수면 1로 지정
	if(mtype % 2 == 0)
		mtype = 2;
	else if (mtype % 2 == 1)
		mtype = 1;

	mesg.mtype = mtype;

	//보낼 내용을 argv에서 복사하고
	strcpy(mesg.mtext, argv[2]);
	//msg send
	if(msgsnd(msgid, (void *)&mesg, 80, IPC_NOWAIT) == -1) {
		perror("msgsnd");
		exit(1);
	}
	return 0;
}
