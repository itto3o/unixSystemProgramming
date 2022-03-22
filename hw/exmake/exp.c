#include <stdio.h>

int Myexp(int number, int exp) {
	int result = 1;

	for(int i = 0; i < exp; i++) {
		result = result * number;	
	}

	return result;
}
