#include <string.h>

//내가 만든 mystrcpy.h를 포함시킨다.
#include "mystrcpy.h"

void mystrcpy(char *dst, char *src) {
	char* temp;
	for(temp = dst; *dst = *src; dst++, src++);

}
