#pragma once
#include "accumulator.h"

enum lexer_tokenTypes {id, op, num, nl, gp, kw};
static const char * tokenTypesNames[6] = {"identifier", "operation", "number", "newline", "grouping", "keyword"};
static const int tokenTypesLength[6] = {10, 9, 6, 7, 8, 7};
static const int longestNameLength = 10;

typedef struct token {
	int type;
	char * toke;
} lexer_token;

typedef struct lexer {
	char * fileName;
	char ** packagePath;
	char header;         // is body if false
	token ** tokens;     // of type token
} lexer;

lexer * lexer_lex(char * file, char ** path, char * body);
char * lexer_toString(lexer * lx);
char * lexer_token_toString(token * tk);
