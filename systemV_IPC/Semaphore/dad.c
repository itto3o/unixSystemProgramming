#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

int main(int argc, char* argv[]) {
	int fd;
	sem_t *sem;
	//mom과 동일한 이름의 세마포어 생성
	char *name = "semaphore";
	sem = sem_open(name, 0, 0777, 0);

	//아빠가 잠시 후에 도착하도록 random 수 생성
	srand(time(NULL));


	printf("Dad comes home. \n");
	sleep(rand()%2);
	//아빠가 엄마보다 늦게 집에 와서 냉장고 확인
	//세마포어의 수가 1이 될 때까지(냉장고에 milk가 생길 때까지 기다리기)
	sem_wait(sem);
	printf("Dad checks the fridge.\n");

	fd = open("fridge", O_CREAT | O_RDWR | O_APPEND, 0777);
	//만약 냉장고에 milk가 없다면 사러 가기
	if(lseek(fd, 0, SEEK_END) == 0) {
		printf("Dad goes to buy milk...\n");
		sleep(2);
		write(fd, "milk ", 5);
		printf("Dad puts milk in fridge and leaves. \n");
		//사러 간 후에 이미 milk가 있다면 너무 많다는 문구 출력
		if(lseek(fd, 0, SEEK_END) > 5)
			printf("What a waste of food! The fridge cannot hold so much milk!\n");
	}
	//냉장고에 milk가 이미 있다면 그대로 떠나기
	else
		printf("Dad closes\n");

	//critical section 종료 후 +1
	sem_post(sem);
	sem_unlink(name);

	return 0;
}
