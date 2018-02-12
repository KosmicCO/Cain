#include "lexer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Define helpers

char * intToString(int x) {
	int len = snprintf(0, 0, "%i", x);
	char * str = calloc(len + 1, sizeof(char));
	snprintf(str, len + 1, "%i", x);
	return str;
}

int searchKeywords(const char * str) {
	return binarySearchKeywords(str, 0, NUM_KEYWORDS - 1);
}

int binarySearchKeywords(const char * str, int l, int h) {
	if (h >= l) {
		int mid = l + (h - l) / 2;
		int comp = strcmp(str, KEYWORDS[mid]);
		if (comp == 0)
			return mid;

		if (comp > 0)
			return binarySearchKeywords(str, l, mid - 1);

		return binarySearchKeywords(str, mid + 1, h);
	}
	return -1;
}

// Lexer functions

void lexer_initialize() {
	qsort(KEYWORDS, NUM_KEYWORDS, sizeof(char *), strcmp);
	initialized = 1;
}

lexer * lexer_lex(const char * file, const char * body) {
	if (!initialized) {
		return 0;
	}
}

char * lexer_toString(const lexer * lx) {
	char * str = "";
	strcat(str, lx->include);
	if (lx->header) {
		strcat(str, " (.ch), ");
	}
	else {
		strcat(str, " (.cb), ");
	}
	char * tokensSize = intToString(lx->size);
	strcat(str, tokensSize);
	strcat(str, " tokens");
	free(tokensSize);
	return str;
}

char * lexer_token_toString(const token * tk, int shorten) {
	char * str = "";
	if (shorten) {
		strcat(str, TOKEN_TYPES_SHORT[tk->type]);
	}
	else {
		strcat(str, TOKEN_TYPES_NAMES[tk->type]);
	}
	strcat(str, ": ");
	strcat(str, tk->toke);
	return str;
}