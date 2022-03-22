#include <stdio.h>

//내가 만든 mystrcpy의 헤더파일을 include한다.
#include "mystrcpy.h"


int main() {
	
	char str[80];
	mystrcpy(str, "Hello");
	puts(str);

}
