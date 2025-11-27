#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
    KEYWORD,TOK_IDENTIFIER, INTEGER_LITERAL, CHAR_LITERAL, STRING_LITERAL, FLOAT_LITERAL, UNIDENTIFIED, TOK_PLUS, TOK_MINUS, 
    TOK_STAR, TOK_SLASH, TOK_IF, TOK_RETURN, TOK_COMMA, TOK_SEMICOLON, TOK_WHILE, TOK_FUNC, TOK_EQ, TOK_EQEQ, TOK_LPAREN,
    TOK_RPAREN, TOK_EOF, TOK_ERROR, TOK_LBRACE, TOK_RBRACE, TOK_LSQRTBRAK, TOK_RSQRTBRAK, TOK_DOUBLEPOINT
} Tokentype;

typedef struct {
    Tokentype type;
    char* lexeme;
    int line;
    int length;
} Tokenstruct;

const char* tokenTypeToString(int type);
Tokenstruct *lexicalAnalyzer (char* input);
Tokenstruct *maketokenChar (Tokenstruct *tokenlist, int count, Tokentype type, char chr, int length, int line);
Tokenstruct *maketokenString (Tokenstruct *tokenlist, int count, Tokentype type, char *sub, int length, int line);

#endif