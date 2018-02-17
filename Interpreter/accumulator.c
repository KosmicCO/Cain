#include "accumulator.h"
#include <stdio.h>
#include <stdlib.h>

// Define helper functions

void * freeNext(node * prev) {
	void * ret = prev->next->item;
	node * aft = prev->next->next;
	free(prev->next);
	prev->next = aft;
	return ret;
}

void * removeFirst(accu * ac) {
	if (!ac->size) {
		return 0;
	}
	ac->size--;
	if (ac->size == 1) {
		void * ret = ac->last->item;
		free(ac->last);
		ac->last = 0;
		return ret;
	}
	return freeNext(ac->last);
}

// Accumulator functions

accu * accu_new() {
	accu * ac = malloc(sizeof(accu));
	ac->last = 0;
	ac->size = 0;
	return ac;
}

void accu_add(accu * ac, const void * o) {
	if (!ac->size) {
		ac->last = malloc(sizeof(node));
		ac->last->next = ac->last;
		ac->last->item = o;
	}
	else {
		node * n = malloc(sizeof(node));
		n->next = ac->last->next;
		n->item = o;
		ac->last->next = n;
		ac->last = n;
	}
	ac->size++;
}

void ** accu_clear(accu * ac) {
	void ** ret = calloc(ac->size, sizeof(void *));
	for (int i = 0; i < ac->size; i++) {
		ret[i] = removeFirst(ac);
	}
	return ret;
}