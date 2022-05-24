#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

struct mymsgbuf {
	long mtype;
	char mtext[80];
};

int main(int argc, char* argv[]) {
	struct mymsgbuf inmsg;
	key_t key;
	int msgid, len;

	key = ftok("keyfile", 1);
	if((msgid = msgget(key, 0)) < 0) {
		perror("msgget error");
		exit(0);
	}

	len = msgrcv(msgid, &inmsg, 80, 2, 0);
	printf("Received Msg = %s, Len = %d\n", inmsg.mtext, len);

	return 0;
}
