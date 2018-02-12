#pragma once
#include "accumulator.h"

enum lexer_tokenTypes {id, op, num, nl, gp, kw, an, str};
static const char * TOKEN_TYPES_NAMES[8] = { "identifier", "operator", "number", "newline", "grouping", "keyword", "annotation", "string" };
static const char * TOKEN_TYPES_SHORT[8] = { "id", "op", "nm", "nl", "gp", "kw", "an", "st" };
static const int LONGEST_TOKEN_NAME_LENGTH = 10;

static const int NUM_KEYWORDS = 28;
static const char * KEYWORDS[28] = { "class", "assert", "this", "for", "while", "do", "public", "protected", "private", "extends",
	"int", "unsigned", "double", "float", "char", "short", "long", "struct", "namespace", "free",
	"alloc", "else", "switch", "redef", "as", "package", "func", "native" };

static int initialized = 0;

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

void lexer_initialize();
lexer * lexer_lex(char * file, char * body);
char * lexer_toString(const lexer * lx);
char * lexer_token_toString(const token * tk, int shorten);
