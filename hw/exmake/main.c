#include <stdio.h>

int main(int argc, char* argv[]) {
	int number = 0;
	int expNumber = 0;

	printf("밑수와 지수를 입력하시오.");
	scanf("%d %d", &number, &expNumber);

	int anwser = Myexp(number, expNumber);
	printf("%d\n", anwser);

	return 0;
}
