#pragma once

typedef struct {
	node * next;
	void * item;
} node;

typedef struct linked_list {
	node * last;
	int size;
}linked_list;

void * get(linked_list * ll, int index);
void append(linked_list * ll, void * item);
void * remove(linked_list * ll, int index);
void removeItem(linked_list * ll, void * item);
void ** clear(linked_list * ll);