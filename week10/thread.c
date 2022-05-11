#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

//thread에 쓸 thread function
void *PrintArg(void* argv) {
	int i;

	//return할 문장을 동적 메모리 할당
	char* comment = (char*)malloc(sizeof(char) * 30);
	comment = "thread over!";
	//파라미터를 받아서 먼저 출력
	printf("%s\n", (char*)argv);

	//2초마다 문장 출력 3번
	for(i = 0; i < 3; i++) {
		sleep(2);
		printf("Thread is running...\n");
	}
	//void* 형으로 바꿔서 return
	return (void*)comment;	
}

int main(int argc, char* argv[]) {
	pthread_t tid;
	void* t_return;

	if(argc != 2) {
		perror("Usage : need 1 argv\n");
		exit(1);
	}
	//thread create
	int state = pthread_create(&tid, NULL, PrintArg, (void*)argv[1]);
	if(state != 0) {
		perror("thread create error\n");
		exit(1);
	}

	//thread가 모두 완료될 때까지 기다리기(join)
	//t_return에 thread function에서 리턴한 값이 들어옴
	int over = pthread_join(tid, &t_return);

	printf("main function running, completed. And %s\n", (char*)t_return);

	return 0;
}
