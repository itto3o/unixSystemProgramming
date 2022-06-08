#include <stdio.h>
typedef struct {
	ItemType buf[MAX_BUF];
	int in;
	int out;
	int counter;
} BoundedBufferType;

int main(int argc, char* argv[]) {
	BoundedBufferType *pBuf;
	int shmid, i, data;

	if((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0) {
		perror("shmat");
		exit(1);
	}	

	srand(time(NULL));

	for(i = 0; i < NLOOPS; i++) {
		if(pbuf->counter == MAX_BUF) {
			printf("Producer: Buffer full. Waiting.....\n");
			while(pBuf->counter == MAX_BUF);
		}

		printf("Producer: Producing a items...\n");
		data = (rand%100)*10000;
		pBuf->buf[pBuf->in].data = data;
		pBuf->in = (pBuf->in + 1) % MAX_BUF;
		pBuf->counter++;

		usleep(data);
		printf("Producer: Produced %d items.....\n", i);
		sleep(2);
		printf("Producer: %d items in buffer.....\n", pBuf->counter);

		if(shmctl(shmid, IPC_RMID, 0) < 0) {
			perror("shmctl");
			exit(1);
		}
	}
}
