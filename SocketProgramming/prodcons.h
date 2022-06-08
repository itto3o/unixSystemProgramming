//최대 2개까지 버퍼에 담을 수 있음
#define MAX_BUF 2

//SHM 파라미터들 선언
#define SHM_KEY ftok("shmfile", 1)
#define SHM_SIZE 1024
#define SHM_MODE IPC_CREAT|0644

#define NLOOPS 20

//data를 담을 아이템 타입
typedef struct {
	int data;
} ItemType;

//버퍼 타입 선언
typedef struct {
	ItemType buf[MAX_BUF];
	int in;
	int out;
	int counter;
} BoundedBufferType;
