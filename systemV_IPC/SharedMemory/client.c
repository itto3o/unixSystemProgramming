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

	//flag와 buf를 malloc으로 동적할당
	char* buf = (char*)malloc(sizeof(char) * BUF_SIZE);
	int* flag = (int*)malloc(sizeof(int));
	//client의 초기 flag값은 0
	*flag = 0;

	//server와 동일한 shmfile에서 key 생성 후 shm 생성
	key = ftok("shmfile", 1);
	shmid = shmget(key, BUF_SIZE, 0);
	if(shmid == -1) {
		perror("shmget error");
		exit(1);
	}

	//shm을 사용할 수 있도록 attach
	shmaddr = shmat(shmid, NULL, 0);
	memset(shmaddr, 0, sizeof(shmaddr));

	while(1) {
		//계속 shm의 flag값을 읽어오다가 1이 되면 수행
		*flag = *((int*)shmaddr);
		if((*flag) == 1) {
			//1일 때 공유메모리의 내용을 읽어오고 출력
			strcpy(buf, ((char*)shmaddr + sizeof(int*)));
			printf("Server Said : %s\n", buf);

			//출력 후 입력
			printf("Client >> ");
			fgets(buf, BUF_SIZE, stdin);
			
			//flag를 0으로 바꾸고 memcpy로 shm에 write
			*flag = 0;
			memcpy(shmaddr, flag, sizeof(int*));
			memcpy(((char*)shmaddr + sizeof(int*)), buf, sizeof(buf));
			//shmaddr = (void*)flag;
			//strcpy(((char*)shmaddr + sizeof(int*)), buf);
		}
	}
	shmdt(shmaddr);
	
	free(flag);
	free(buf);
	return 0;
}
