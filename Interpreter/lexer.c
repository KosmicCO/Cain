#include "lexer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "accumulator.h"

const int TOKEN_BUFFER_SIZE = 256;

// TODO: make sure to replace all string strcat or strcpy with a safe version (this is currently broken)

// Define helpers

char * intToString(int x) {
	int len = snprintf(0, 0, "%i", x);
	char * str = calloc(len, sizeof(char));
	snprintf(str, len, "%i", x);
	return str;
}

int isInclusiveSymbol(char c) {
	if (0x21 <= c && c <= 0x2F) return 1;
	if (0x3A <= c && c <= 0x40) return 1;
	if (0x5B <= c && c <= 0x5E) return 1;
	return 0x7B <= c && c <= 0x7E;
}

int isExcudedSymbol(char c) { // returns index + 1
	for (int i = 0; i < NUM_EXCLUDED_SYMBOLS; ++i) {
		if (c == EXCLUDE_SYMBOLS[i]) return i + 1;
	}
	return 0;
}

int isAlphabetical(char c) {
	if (0x41 <= c && c <= 0x5A) return 1;
	return 0x61 <= c && c <= 0x7A;
}

int isNumerical(char c) {
	return 0x30 <= c && c <= 0x39;
}

int isAlphaNumeric(char c) {
	if (isAlphabetical(c) || isNumerical(c)) return 1;
	return c == '_';
}

int isWhiteSpace(char c) {
	return c == '\t' || c == '\n' || c == ' ';
}

void addNewToken(accu * tokens, int type, char * toke) {
	lexer_token * token = malloc(sizeof(lexer_token));
	token->type = type;
	token->toke = toke;
	accu_add(tokens, token);
}

int startToken(char * buffer, int * bufferSize, accu * tokens, char c) {
	if (isAlphabetical(c)) {
		buffer[(*bufferSize)++] = c;
		return id;
	}
	if (isNumerical(c)) {
		buffer[(*bufferSize)++] = c;
		return num;
	}
	else if (isInclusiveSymbol(c)) {
		int ind = isExcudedSymbol(c);
		switch (ind) {
		case 0:
			buffer[(*bufferSize)++] = c;
			return op;
		case 1: return str;
		case 2:
			buffer[(*bufferSize)++] = c;
			return num;
		case 9:
			addNewToken(tokens, stp, "");
			return -1;
		case 10: return an;
		default: { // 3-8
			char * bracket = calloc(1, sizeof(char));
			bracket[0] = EXCLUDE_SYMBOLS[ind - 1];
			addNewToken(tokens, brk, bracket);
			return -1;
		}
		}
	}
}

void endToken(char * buffer, int bufferSize, accu * tokens, int type) {
	char * toke = calloc(strlen(buffer), sizeof(char));
	strncpy(toke, bufferSize, buffer);                         // TODO: check string operation
	switch (type) {
	case id:
		if (lexer_info_searchKeywords(buffer)) {
			addNewToken(tokens, kw, toke);
		}
		addNewToken(tokens, id, toke);
		break;
	case op:
		addNewToken(tokens, op, toke);
		break;
	case num:
		addnewToken(tokens, num, toke);
		break;
	case an:
		addNewToken(tokens, an, toke);
		break;
	case str:
		addNewToken(tokens, str, toke);
	}
}

// Lexer functions

lexer * lexer_lex(const char * file, int isHeader, const char * body) {
	if (!initialized) {
		return 0;
	}

	lexer * lex = malloc(sizeof(lexer));
	int fileSize = strlen(file);
	lex->include = calloc(fileSize + 1, sizeof(char));
	strncpy(lex->include, fileSize, file);
	lex->header = isHeader;

	accu * tokens = malloc(sizeof(tokens));

	char * buffer = calloc(TOKEN_BUFFER_SIZE, sizeof(char));
	int bufferSize = 0;
	int type = -1;

	char c = body[0];
	int bodyIndex = 1;
	while (!(c == '\z' || c == 0x00)) {
		if (type == -1) {
			if (!isWhiteSpace(c)) type = startToken(buffer, &bufferSize, tokens, c);
			c = body[bodyIndex++];
		}
		else {
			if (type != str) {
				int nextToken = 0;
				if (isWhiteSpace(c)) {
					c = body[bodyIndex++];
					nextToken = 1;
				}
				else {
					switch (c) {
					case id:
					case num:
					case an:
						nextToken = !isAlphaNumeric(c);
						break;
					case op:
						nextToken = !isInclusiveSymbol(c) || isExcudedSymbol(c);
						break;
					}
				}
				if (nextToken) {
					type = -1;
					endToken(buffer, bufferSize, tokens, type);
					bufferSize = 0;
				}else {
					buffer[bufferSize++] = c;
					c = body[bodyIndex++];
				}
			}
			else {
				int startStr = bodyIndex - 1;
				int strSize = 0;
				int isEscaped = 0;
				while (!(c == '\n' || c == 0x00)) {
					if (isEscaped) {
						isEscaped = 0;
					}
					else {
						if (c == '\"') {
							c = body[bodyIndex++];
							break;
						}
						if (c == '\\') isEscaped = 1;
					}
					c = body[bodyIndex++];
					strSize++;
				}
				type = -1;
				char * subBuffer = calloc(strSize + 1, sizeof(char));
				strncpy(subBuffer, strSize, body + startStr);                     // TODO: check string operation
				endToken(subBuffer, strSize, tokens, str);
			}
		}
	}
	lex->size = tokens->size;
	lex->tokens = (lexer_token *) accu_clear(tokens);
	free(tokens);
	free(buffer);
	return lex;
}

char * lexer_toString(const lexer * lx) {
	char * tokensSize = intToString(lx->size);

	int includeLen = strlen(lx->include);
	int tokenSizeLen = strlen(tokensSize);

	char * str = calloc(includeLen + tokenSizeLen + 16, sizeof(char));
	strncat(str, includeLen, lx->include);                              // TODO: check string operation
	if (lx->header) {
		strncat(str, 8, " (.ch), ");                                    // TODO: check string operation
	}
	else {
		strncat(str, 8, " (.cb), ");                                    // TODO: check string operation
	}
	strncat(str, tokenSizeLen, tokensSize);                             // TODO: check string operation
	strncat(str, 7, " tokens");                                         // TODO: check string operation
	free(tokensSize);
	return str;
}

char * lexer_token_toString(const lexer_token * tk, int shorten) {

	int typeNameLen = strlen(TOKEN_TYPES_NAMES[tk->type]);
	int tokeLen = strlen(tk->toke);

	char * str = calloc(tokeLen + (shorten ? 2 : typeNameLen) + 3, sizeof(char));
	if (shorten) {
		strncat(str, 2, TOKEN_TYPES_SHORT[tk->type]);                  // TODO: check string operation
	}
	else {
		strcat(str, TOKEN_TYPES_NAMES[tk->type]);                      // TODO: check string operation
	}
	strncat(str, 2, ": ");                                             // TODO: check string operation
	strncat(str, tokeLen, tk->toke);                                   // TODO: check string operation
	return str;
}