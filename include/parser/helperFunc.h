#ifndef HELPERFUNC_H
#define HELPERFUNC_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"
#include "../lexer/tokenizer.h"

bool isTOKType(Tokentype type);
bool isOperatorExpression (Tokentype type);
ParameterNode *create_param_tree(char *name, Tokentype type, int count);
void param_list_add(ParameterNode **head, ParameterNode *param);
void add_stmt_list(ASTnode **head, ASTnode **last, ASTnode *stmt, NodeType ast_type);
const char* astTypeToString(NodeType type);
void prinast(ASTnode *node);
void freeASTNode(ASTnode *node);
Tokentype fromTypeToPTR(Tokentype type);

#endif