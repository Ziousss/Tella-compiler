#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
    IDENTIFIER, OPERATOR, DELIMITER, KEYWORD, INTEGER, UNIDENTIFIED
} Tokentype;

typedef struct {
    Tokentype type;
    char* lexeme;
} Tokenstruct;


Tokenstruct *lexicalAnalyzer (char* input);
const char* tokenTypeToString(int type);


#endif