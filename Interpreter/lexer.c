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

// Lexer functions

lexer * lexer_lex(const char * file, const char * body) {

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
		strcat(str, tokenTypesShort[tk->type]);
	}
	else {
		strcat(str, tokenTypesNames[tk->type]);
	}
	strcat(str, ": ");
	strcat(str, tk->toke);
	return str;
}