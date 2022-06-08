#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>

#include "semlib.h"
#include "prodcons.h"

int main() {
	BoundedBufferType *pBuf;
	int shmid, i, data;
	//POSIX semaphore로 sem_open하기 위해 sem_t * 로 선언
	sem_t* emptySemid, *fullSemid, *mutexSemid;

	//공유 메모리를 얻어서 attach
	if((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0) {
		perror("shmget");
		exit(1);
	}

	if((pBuf = (BoundedBufferType *)shmat(shmid, 0, 0)) == (void *) -1) {
		perror("shmat");
		exit(1);
	}
	
	//empty full mutex 세마포어들 초기화
	if((emptySemid = semInit(EMPTY_SEM_KEY)) < 0) {
		fprintf(stderr, "semInit failure\n");
		exit(1);
	}

	if((fullSemid = semInit(FULL_SEM_KEY)) < 0) {
		fprintf(stderr, "semInit failure\n");
		exit(1);
	}

	if((mutexSemid = semInit(MUTEX_SEM_KEY)) < 0) {
		fprintf(stderr, "semInit failure\n");
		exit(1);
	}

	srand(0x9999);
	//20번 반복
	for(i = 0; i< NLOOPS; i++) {
		//critical section을 위해 full과 mutex -1
		if(semWait(fullSemid) < 0) {
			fprintf(stderr, "semWait failure\n");
			exit(1);
		}
		if(semWait(mutexSemid) < 0) {
			fprintf(stderr, "semWait failure\n");
			exit(1);
		}
//
//		if(pBuf->counter == 0) {
//			printf("Consumer: Buffer empty. Waiting.....\n");
//			while(pBuf->counter == 0);
//		}
		printf("Consumer: Consuming an item.....\n");

		//data 읽어오고 counter--
		data = pBuf->buf[pBuf->out].data;
		pBuf->out = (pBuf->out + 1) % MAX_BUF;
		pBuf->counter--;

		//mutex와 empty +1
		if(semPost(mutexSemid) < 0) {
			fprintf(stderr, "semPost failure\n");
			exit(1);
		}
		if(semPost(emptySemid) < 0) {
			fprintf(stderr, "semPost failure\n");
			exit(1);
		}
		usleep((rand()%100)*10000);
	}

	printf("Consumer: Consumed %d items.....\n", i);
	printf("Consumer: %d items in buffer.....\n", pBuf->counter);
//
//	if(semDestroy(EMPTY_SEM_KEY) < 0) {
//		fprintf(stderr, "semDestroy failure\n");
//	}
//
//	if(semDestroy(FULL_SEM_KEY) < 0) {
//		fprintf(stderr, "semDestroy failure\n");
//	}
//
//	if(semDestroy(MUTEX_SEM_KEY) < 0) {
//		fprintf(stderr, "semDestroy failure\n");
//	}
//
	return 0;

}
