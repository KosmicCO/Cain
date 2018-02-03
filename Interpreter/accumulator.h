#pragma once

typedef struct accu_node node;

struct accu_node {
	node * next;
	void * item;
};

typedef struct accu {
	node * last;
	int size;
} accu;

accu * accu_new();
void accu_add(accu * ac, void * o);
void ** accu_clear(accu * ac);