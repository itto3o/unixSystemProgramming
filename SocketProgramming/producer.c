#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <string.h>
#include "semlib.h"
#include "prodcons.h"

int main(int argc, char* argv[]) {
	BoundedBufferType *pBuf;
	int shmid, i, data;
	//POSIX sem_open을 위해 id들을 sem_t로 선언
	sem_t *emptySemid, *fullSemid, *mutexSemid;

	//공유 메모리 생성 후 attach
	if((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0) {
		perror("shmget");
		exit(1);
	}	
	if((pBuf = (BoundedBufferType *)shmat(shmid, 0, 0)) == (void *) -1) {
		perror("shmat");
		exit(1);
	}

	//semaphore init -empty, full, mutex
	//empty = N, full = 0, mutex = 1
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
	srand(0x8888);

	//20번 반복
	for(i = 0; i < NLOOPS; i++) {
		//empty와 mutex로 critical section create
		if(semWait(emptySemid) < 0) {
			fprintf(stderr, "semWait failure\n");
			exit(1);
		}
		if(semWait(mutexSemid) < 0) {
			fprintf(stderr, "semWait failure\n");
			exit(1);
		}
//		if(pbuf->counter == MAX_BUF) {
//			printf("Producer: Buffer full. Waiting.....\n");
//			while(pBuf->counter == MAX_BUF);
//		}
		
		//item 생성
		printf("Producer: Producing a items...\n");
		data = (rand()%100)*10000;

		//buf크기만큼 생성 후 counter++
		pBuf->buf[pBuf->in].data = data;
		pBuf->in = (pBuf->in + 1) % MAX_BUF;
		pBuf->counter++;

		//값을 변경하고 post
		if(semPost(mutexSemid) < 0) {
			fprintf(stderr, "semPost failure\n");
			exit(1);
		}
		if(semPost(fullSemid) < 0) {
			fprintf(stderr, "semPost failure\n");
			exit(1);
		}

		usleep(data);
	}

	//반복이 끝난 후 버퍼에 몇 개 남았는지 보여주고 종료
	printf("Producer: Produced %d items.....\n", i);
	sleep(2);
	printf("Producer: %d items in buffer.....\n", pBuf->counter);

	//세마포어들 삭제
	if(semDestroy(EMPTY_SEM_KEY) < 0) {
		fprintf(stderr, "semDestroy failure\n");
	}
	if(semDestroy(FULL_SEM_KEY) < 0) {
		fprintf(stderr, "semDestroy failure\n");
	}
	if(semDestroy(MUTEX_SEM_KEY) < 0) {
		fprintf(stderr, "semDestroy failure\n");
	}
//		if(shmctl(shmid, IPC_RMID, 0) < 0) {
//			perror("shmctl");
//			exit(1);
//		}
	return 0;
//
}
