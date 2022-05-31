#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <semaphore.h>

int main(int argc, char* argv[]) {
	int fd;
	sem_t *sem;
	//이름있는 POSIX 세마포어 생성
	char* name = "semaphore";
	sem = sem_open(name, O_CREAT, 0777, 1);

	//mom이 집에 오고 냉장고를 check할 때부터 critical section
	printf("Mom comes home. \n");
	sem_wait(sem);
	printf("Mom checks the fridge.\n");

	fd = open("fridge", O_CREAT | O_RDWR | O_APPEND, 0777);
	//냉장고에 우유가 없다면
	if(lseek(fd, 0, SEEK_END) == 0) {
		//milk사러가기
		printf("Mom goes to buy milk...\n");
		sleep(2);
		//write milk
		write(fd, "milk ", 5);
		printf("Mom puts milk in fridge and leaves. \n");
		//냉장고에 이미 milk가 있었다면 너무 많다는 문구 출력
		if(lseek(fd, 0, SEEK_END) > 5)
			printf("What a waste of food! The fridge cannot hold so much milk!\n");
	}
	else
		printf("Mom closes\n");

	//critical section 종료, post로 +1
	sem_post(sem);
	sem_unlink(name);

	return 0;
}
