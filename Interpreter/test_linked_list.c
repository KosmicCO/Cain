#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int main() {
	linked_list * ll = newLinkedList();
	int t = 5;
	int g = 7;
	append(ll, &t);
	append(ll, &g);
	int ** list = (int **) clear(ll);
	free(ll);
	for (int i = 0; i < 2; i++) {
		printf("%i", * list[i]);
	}
	printf("%s", "end");
}