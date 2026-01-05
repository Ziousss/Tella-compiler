#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ast.h"
#include "../lexer/tokenizer.h"

ASTnode *funcDefparse(Tokenstruct *tokenList, int *index);
ASTnode *parameterParse(Tokenstruct *tokenList, int *index);
ASTnode *blockParse(Tokenstruct *tokenList, int *index);

#endif