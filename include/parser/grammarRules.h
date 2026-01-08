#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ast.h"
#include "../lexer/tokenizer.h"

ASTnode *funcDefParse(Tokenstruct *tokenList, int *index);
ParameterNode *parameterParse(Tokenstruct *tokenList, int *index);
ASTnode *blockParse(Tokenstruct *tokenList, int *index);
ASTnode *funcCallParse(Tokenstruct *tokenList, int *index);
ASTnode *declarationParse(Tokenstruct *tokenlist, int *index);
ASTnode *assignParse(Tokenstruct *tokenList, int *index);
ASTnode *expressionParse(Tokenstruct *tokenList, int *index);
ASTnode *ifStmtParse(Tokenstruct *tokenList, int *index);
ASTnode *forStmtParse(Tokenstruct *tokenList, int *index);
ASTnode *whileStmtParse(Tokenstruct *tokenList, int *index);
ASTnode *returnStmtParse(Tokenstruct *tokenList, int *index);
ASTnode *programParse(Tokenstruct *tokenList, int *index);

#endif