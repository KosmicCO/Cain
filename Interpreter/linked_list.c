#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

// Helper pre-declarations

void * removeFirst(linked_list * ll);
void * freeNext(node * prev);

// linked_list mutation functions;

linked_list * newLinkedList() {
	linked_list * ll = malloc(sizeof(linked_list));
	ll->last = 0;
	ll->size = 0;
	return ll;
}

void * get(linked_list * ll, int index) {
	node * cur = ll->last->next;
	for (int i = 0; i < ll->size; i++) {
		if (i == index) {
			return cur->item;
		}
		cur = cur->next;
	}
	return 0;
}

void append(linked_list * ll, void * item) {
	if (ll->last) {
		node * n = malloc(sizeof(node));
		n->next = ll->last->next;
		ll->last->next = n;
		ll->last = n;
	} else {
		ll->last = malloc(sizeof(node));
		ll->last->next = ll->last;
	}
	ll->last->item = item;
	ll->size++;
}

void * removeIndex(linked_list * ll, int index) {
	if (index < 0 || !ll->size) return 0;
	ll->size--;
	if (ll->size == 1) {
		void * ret = ll->last->item;
		free(ll->last);
		ll->last = 0;
		return ret;
	}
	node * prev = ll->last;
	index %= ll->size;
	for (int i = 0; i < ll->size; i++) {
		if (i == index) break;
		prev = prev->next;
	}
	return freeNext(prev);
}

void removeItem(linked_list * ll, void * item) {
	if (!ll->size) return;
	node * prev = ll->last;
	int found = 0;
	for (int i = 0; i < ll->size; i++) {
		if (prev->next->item == item) {
			found = 1;
			break;
		}
		prev = prev->next;
	}
	if (!found) return;
	if (ll->size == 1) {
		free(ll->last);
		ll->last = 0;
	} else {
		node * aft = prev->next->next;
		free(prev->next);
		prev->next = aft;
	}
	ll->size--;
}

void ** clear(linked_list * ll) {
	void ** ret = calloc(ll->size, sizeof(void *));
	for (int i = 0; i < ll->size; i++) {
		ret[i] = removeFirst(ll);
	}
	ll->size = 0;
	return ret;
}

// Helper function declarations

void * removeFirst(linked_list * ll) {
	if (!ll->size) {
		return 0;
	} else if (ll->size == 1) {
		void * ret = ll->last->item;
		free(ll->last);
		ll->last = 0;
		return ret;
	}
	return freeNext(ll->last);
}

void * freeNext(node * prev) {
	void * ret = prev->next->item;
	node * aft = prev->next->next;
	free(prev->next);
	prev->next = aft;
	return ret;
}