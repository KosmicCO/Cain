#include <stdio.h>
#include <stdlib.h>

int main() {
	for (char i = 0; i < 256; i++) {
		printf("%c", i);
	}
	printf("end");
	return 0;
}