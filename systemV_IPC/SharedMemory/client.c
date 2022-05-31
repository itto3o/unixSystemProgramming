#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main(int argc, char* argv[]) {
	key_t key;
	int shmid;
	void* shmaddr;
	char buf[BUF_SIZE];
	int flag = 0;

	key = ftok("shmfile", 1);
	shmid = shmget(key, BUF_SIZE, IPC_CREAT|0666);
	if(shmid == -1) {
		perror("shmget error");
		exit(1);
	}

	shmaddr = shmat(shmid, NULL, 0);

	while(1) {
		flag = *((int*)shmaddr);
		printf("%d\n", flag);
		if(flag == 1) {
			strcpy(buf, shmaddr);
			printf("Server Said :%s\n", buf);

			printf("Client >>");
			fgets(buf, BUF_SIZE, stdin);
			flag = 0;
			shmaddr = &flag;
			strcpy(shmaddr + sizeof(int), buf);
		}
	}
	
	return 0;
}
