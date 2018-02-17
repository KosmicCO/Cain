#pragma once
#include "accumulator.h"
#include "lexer_info.h"

typedef struct lexer_token {
	int type;
	char * toke;
} lexer_token;

typedef struct lexer {
	char * include;
	int header;         // is body if false
	lexer_token ** tokens;
	int size;            // size of tokens array
} lexer;

lexer * lexer_lex(char * file, char * body);
char * lexer_toString(const lexer * lx);
char * lexer_token_toString(const lexer_token * tk, int shorten);
