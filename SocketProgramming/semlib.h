#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

//이름있는 sem을 위해 이름 지정
#define EMPTY_SEM_KEY	"empty"
#define FULL_SEM_KEY	"full"
#define MUTEX_SEM_KEY	"mutex"

//semInit
sem_t* semInit(char* semName) {
	return (sem_open(semName, O_CREAT, 0777, 2));
}

int semWait(sem_t* semid) {
	if(sem_wait(semid) == -1)
		return -1;
	return 0;
}

int semPost(sem_t* semid) {
	if(sem_post(semid) == -1)
		return -1;
	return 0;
}		

//unlink를 쓰려면 char*이 파라미터로 들어와야 함
int semDestroy(char* semName) {
	if(sem_unlink(semName) == -1)
		return -1;
	return 0;
}
