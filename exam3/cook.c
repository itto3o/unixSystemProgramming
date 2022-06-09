#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

//waiting...
//스르로 주문 x, 남이 주문을 해줘야 함 -> 다른 프로세스에서 ps-ef |grep cook ==> pid에 시그너 보내기
//kill -USR1 607628에 날리면
//cook1이 10초를 출력하고 cokking completed 후 waiting...
//SIGINT 무시

//2번째
//부모 프로세스는 주문을 받으면 자식에게 주문을 전달
//==> 외부가 아니라 부모가 자식에게 주문(y는 주문전달, n는 주문완료)
//SIGUSR1로 자식프로세스에게 주문
//주문이 없는 상태에서 SIGINT는 자녀를 먼저 죽이고 부모 죽이기
//자식은 주문받아서 요리시작, (앞에서 만들었던 프로그램 돌리기), 완료되면 부모에게 SIGUSR1에 알림
//부모는 음식 완료 출력

// order를 실행하면 y? n? ==> y는 자식이 cook2를 실행, 쿠킹이 끝나면 자식이 먼저 끝나기
// n을 누르면 kill child process 후에 종료

//그러면 cook은 10초를 출력하고, SIGINT를 받으면 무시하도록 ==> 그런데 이게 부모, 자식 모두 등록되어 있어야 하니까
//얘는 order에서 수행해야 할듯
//

int sec = 10;
void handler(int signo) {
	printf("Cooking ... %d\n", sec--);
}

void timer() {
	while(sec > 0) {
		alarm(1);
		pause();
	}
}

void exitHandler(int signo) {
	printf("child exit\n");
	//kill(getppid(), SIGINT);
}

int main(int argc, char* argv[]) {
//fork를 먼저해서,
//부모는 y? n?를 출력하고, y면 자식에게 USR1 신호 보내기, 자식은 USR1신호를 받으면 cook수행
//n이면 자식 pid로 kill
//시그널 블록을 이용해서 프로세스 동작중엔 SIGINT 무시
//USR1 신호를 받은 자식은 cook을 실행하고, 실행 완료되면 

	sigset_t sig;
	sigemptyset(&sig);
	sigaddset(&sig, SIGINT);

	signal(SIGINT, exitHandler);
	signal(SIGALRM, handler);
	sigprocmask(SIG_BLOCK, &sig, (sigset_t *)NULL);

	timer();
	printf("Cooking Completed.\n");
	//이게 안먹히네
	//kill(getppid(), SIGUSR1);

	sigprocmask(SIG_UNBLOCK, &sig, (sigset_t*)NULL);
	//kill(getpid(), SIGINT);
	exit(0);
	return 0;
}
