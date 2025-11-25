#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int lexicalAnalyzer (char* input);

enum Tokentype {
    IDENTIFIER, OPERATOR, DELIMITER, KEYWORD, INTEGER, UNIDENTIFIED
};

typedef struct {
    enum Tokentype type;
    char* lexeme;
} Tokenstruct;

#endif