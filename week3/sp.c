#include <stdio.h>

int global = 2;

int func(int a, int b) {
	static int scale = 1;
	int result = (a + b) * global * scale;
	scale *= 10;

	return result;
}

int main() {
	printf("result = %d\n", func(10, 20));
	printf("result = %d\n", func(10, 20));
}
