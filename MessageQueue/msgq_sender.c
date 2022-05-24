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
	if(argc != 3) {
		printf("Usage %s mtype msg", argv[0]);
		exit(1);
	}

	key_t key;
	int msgid;
	int mtype;
	struct mymsgbuf mesg;

	key = ftok("keyfile", 1);
	msgid = msgget(key, IPC_CREAT|0644);
	if(msgid == -1) {
		perror("msggmet error");
		exit(1);
	}
	mtype = atoi(argv[1]);
	if(mtype % 2 == 0)
		mtype = 2;
	else if (mtype % 2 == 1)
		mtype = 1;

	mesg.mtype = mtype;
	strcpy(mesg.mtext, argv[2]);
	if(msgsnd(msgid, (void *)&mesg, 80, IPC_NOWAIT) == -1) {
		perror("msgsnd");
		exit(1);
	}
	return 0;
}
