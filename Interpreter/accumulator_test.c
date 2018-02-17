#include "accumulator.h"
#include <stdio.h>
#include <stdlib.h>

static const int NUM_VALS = 20;

int main() {
	int * nums = calloc(NUM_VALS, sizeof(int));
	accu * ac = malloc(sizeof(accu));

	for (int i = 0; i < NUM_VALS; ++i) { 
		nums[i] = i;
		accu_add(ac, &nums + i);
	}

	int accuSize = ac->size;
	int ** accuVals = accu_clear(ac);
	for (int i = 0; i < accuSize; ++i) {
		printf("%x ", *accuVals[i]);
	}
}