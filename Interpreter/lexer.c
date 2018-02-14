#include "lexer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "accumulator.h"

const int TOKEN_BUFFER_SIZE = 256;

// Define helpers

char * intToString(int x) {
	int len = snprintf(0, 0, "%i", x);
	char * str = calloc(len + 1, sizeof(char));
	snprintf(str, len + 1, "%i", x);
	return str;
}

// Lexer functions

lexer * lexer_lex(const char * file, int isHeader, const char * body) {
	if (!initialized) {
		return 0;
	}

	lexer * lex = malloc(sizeof(lexer));
	int fileLen = strlen(file);
	lex->include = calloc(fileLen, sizeof(char));
	strcpy(lex->include, file);
	lex->header = isHeader;

	accu * tokens = malloc(sizeof(tokens));
	char * buffer = calloc(TOKEN_BUFFER_SIZE, sizeof(char));

	// TODO: write body character iterator and helper functions
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