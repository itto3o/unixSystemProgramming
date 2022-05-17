#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

//10초를 잴 sec 변수, 10부터 하나씩 줄여감
int sec = 10;

//alarm 시그널이 오면 sec를 출력하고 --
void handler(int signo) {
	printf("My Message No.%d\n", sec--);
}		

//kill 시그널이 오면 sec를 출력하고
//time over
void killhandler(int signo) {
	printf("My Message No.%d\n", sec);
	printf("Time Over\n");
	exit(0);
}

//while로 sec가 0보다 크면
//alarm으로 1초를 잰 후 시그널 보내기
void stopwatch() {
	while(sec > 0) {
		alarm(1);
		pause();
	}
}

//핸들ㄹ러 등록
void main() {
	signal(SIGALRM, handler);
	signal(SIGINT, killhandler);

	stopwatch();
}

