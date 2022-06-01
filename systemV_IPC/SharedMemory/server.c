#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#define BUF_SIZE 1024

int main(int argc, char* argv[]) {
	key_t key;
	int shmid;
	void* shmaddr;

	//flag와 내용을 malloc 동적 할당
	int* flag = (int*)malloc(sizeof(int));
	char* buf = (char*)malloc(sizeof(char) * BUF_SIZE);
	//server의 초기 플래그 값은 1
	*flag = 1;

	//shmfile에서 key 생성, 공유메모리 생성
	key = ftok("shmfile", 1);
	shmid = shmget(key, BUF_SIZE, IPC_CREAT|0666);
	if(shmid == -1) {
		perror("shmget error");
		exit(1);
	}

	//shm을 사용할 수 있도록 attach
	shmaddr = shmat(shmid, NULL, 0);
	memset(shmaddr, 0, sizeof(shmaddr));

	//server에서 입력 먼저 시작
	printf("Server >> ");
	fgets(buf, BUF_SIZE, stdin);

	//받아온 값을 memcpy로 shmaddr에 입력,
	//첫 부분에는 flag를, flag다음에는 contents를 입력
	memcpy(shmaddr, flag, sizeof(int*));
	memcpy(((char*)shmaddr + sizeof(int*)), buf, sizeof(buf));
	//shmaddr = (void*)flag;

	while(1) {
		//shm의 flag를 계속 읽어오다가
		*flag = *((int*)shmaddr);
		//flag가 0일 때 수행
		if((*flag) == 0) {
			//buf에 shm에서 읽어온 내용을 넣고 출력
			strcpy(buf, ((char*)shmaddr + sizeof(int*)));
			printf("Client Said : %s\n", buf);

			//출력 후 입력하기
			printf("Server >> ");
			fgets(buf, BUF_SIZE, stdin);
			//flag를 1로 바꾸고
			*flag = 1;
			//flag와 입력한 내용을 memcpy로 write
			memcpy(shmaddr, flag, sizeof(int*));
			memcpy(((char*)shmaddr + sizeof(int*)), buf, sizeof(buf));
		}
	}
	shmdt(shmaddr);

	free(flag);
	free(buf);
	
	return 0;
}
