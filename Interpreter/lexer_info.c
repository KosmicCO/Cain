#include "lexer_info.h"
#include <string.h>

// Define helpers

int binarySearch(const char * str, char ** list, int l, int h) {
	if (h >= l) {
		int mid = l + (h - l) / 2;
		int comp = strcmp(str, list[mid]);
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
	return binarySearch(str, 0, KEYWORDS, NUM_KEYWORDS - 1);
}

