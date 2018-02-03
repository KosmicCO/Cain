#pragma once

typedef struct node node;

struct node {
	node * next;
	void * item;
};

typedef struct linked_list {
	node * last;
	int size;
}linked_list;

linked_list * newLinkedList();
void * get(linked_list * ll, int index);
void append(linked_list * ll, void * item);
void * removeIndex(linked_list * ll, int index);
void removeItem(linked_list * ll, void * item);
void ** clear(linked_list * ll);