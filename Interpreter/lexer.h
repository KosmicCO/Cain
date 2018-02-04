#pragma once
#include "accumulator.h"

enum lexer_tokenTypes {id, op, num, nl, gp, kw};
static const char * tokenTypesNames[6] = { "identifier", "operation", "number", "newline", "grouping", "keyword" };
static const char * tokenTypesShort[6] = { "id", "op", "nm", "nl", "gp", "kw" };
static const int longestNameLength = 10;

typedef struct lexer_token {
	int type;
	char * toke;
} token;

typedef struct lexer {
	char * include;
	char header;         // is body if false
	token ** tokens;
	int size;            // size of tokens array
} lexer;

lexer * lexer_lex(char * file, char * body);
char * lexer_toString(const lexer * lx);
char * lexer_token_toString(const token * tk, int shorten);
