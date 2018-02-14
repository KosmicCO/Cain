#include "lexer_info.h"
#include <string.h>

// Define helpers

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

// Lexer_info functions

void lexer_info_initialize() {
	qsort(KEYWORDS, NUM_KEYWORDS, sizeof(char *), strcmp);
	initialized = 1;
}

int lexer_info_searchKeywords(const char * str) {
	return binarySearchKeywords(str, 0, NUM_KEYWORDS - 1);
}

