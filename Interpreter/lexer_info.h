#pragma once

enum lexer_info_tokenTypes { id, op, num, brk, kw, an, str, stp };
static const char * TOKEN_TYPES_NAMES[8] = { "identifier", "operator", "number", "bracket", "keyword", "annotation", "string", "stop" };
static const char * TOKEN_TYPES_SHORT[8] = { "id", "op", "nm", "bk", "kw", "an", "st", "sp" };
static const int LONGEST_TOKEN_NAME_LENGTH = 10;

static const int NUM_EXCLUDED_SYMBOLS = 10;
static const char * EXCLUDE_SYMBOLS[10] = {'"', '\'', '{', '}', '(', ')', '[', ']', ';', '@'};

static const int NUM_KEYWORDS = 28;
static const char * KEYWORDS[28] = { "class", "assert", "this", "for", "while", "do", "public", "protected", "private", "extends",
"int", "unsigned", "double", "float", "char", "short", "long", "struct", "namespace", "free",
"alloc", "else", "switch", "redef", "as", "package", "native", "void" };

static int initialized = 0;

void lexer_info_initialize();
int lexer_info_searchKeywords(const char * str);