#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
    //general
    TOK_IDENTIFIER, TOK_INTEGER_LITERAL, TOK_CHAR_LITERAL, TOK_STRING_LITERAL, TOK_FLOAT_LITERAL, TOK_UNIDENTIFIED, 
    //Types
    TOK_INT, TOK_CHAR, TOK_VOID,
    //operator
    TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH, TOK_PLUSEQ, TOK_MINUSEQ, TOK_UNEQ, TOK_EQEQ, TOK_GR, TOK_GREQ,
        TOK_LESS, TOK_LESSEQ,
    //keyword
    TOK_IF, TOK_RETURN, TOK_WHILE, TOK_FUNC, TOK_EOF,TOK_ERROR, TOK_CASE, TOK_FOR, TOK_ELSE, TOK_DO,
        TOK_CONTINUE, TOK_BREAK, TOK_SWITCH, TOK_MAIN,
    //delimiter
    TOK_COMMA, TOK_SEMICOLON, TOK_EQ, TOK_LPAREN, TOK_RPAREN, TOK_LBRACE, TOK_RBRACE, 
        TOK_LSQRTBRAK, TOK_RSQRTBRAK, TOK_DOUBLEPOINT, TOK_EXCLAMATION, TOK_DOT,
    //boolean/null
    TOK_TRUE, TOK_FALSE, TOK_NULL
} Tokentype;

typedef struct {
    char *lexeme;
    Tokentype type;
} Keyword;

extern Keyword keywords[];

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
Tokentype keyword_type(char *sub);

#endif