#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

//thread 수 지정
#define THREAD_NUM 8

//thread function, id를 받아와서 i를 증가시키며 출력하고 i가 5가되면 return
void* t_function(void* data) {
	int id;
	int i = 0;
	//result는 동적할당을 해줘야 return한 뒤에도 값이 남아 있다.
	int* result = (int*)malloc(sizeof(int));

	id = *((int *)data);

	while(1) {
		printf("(%lu) %d : %d\n", pthread_self(), id, i);
		i++;
		if(i==5) {
			//i를 직접 return하면 (void*)i에서, int에서 void형으로 형변환이 안되어
			//result를 int*로 선언하고 malloc으로 할당 받았다.
			*result = i;
			return (void*)result;
		}	
		usleep(1000);
	}
}

int main(int argc, char* argv[]) {
	//tid를 배열로 선언하여 thread 수에 따라 생성한다.
	pthread_t tid[THREAD_NUM];
	int id[THREAD_NUM];
	int id_num = 1;
	//id에 thread 수만큼 숫자를 넣는다. 1~n
	for(int i = 0; i < THREAD_NUM; i++)
		id[i] = id_num++;

	//각각의 스레드의 return, result를 담을 배열을 선언
	int *result[THREAD_NUM];

	//thread create
	for(int i = 0; i < THREAD_NUM; i++) 	
		pthread_create(&tid[i], NULL, t_function, &id[i]);

	//thread join & print
	for(int i = 0; i < THREAD_NUM; i++) {
		//원래 result를 void*로 선언해서 받아왔는데 print할때 %d로 출력이 안돼서
		//int*로 선언해서 join 안에서 형변환을 해서 받아오고 %d로 출력한다.
		pthread_join(tid[i], (void**)&result[i]);
		printf("pthread return %d : %d\n", id[i], *result[i]);
	}

	return 0;
}
