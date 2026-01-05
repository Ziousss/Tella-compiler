#ifndef HELPERFUNC_H
#define HELPERFUNC_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"
#include "../lexer/tokenizer.h"

ASTnode *makeFuncNode();
bool isTOKType(Tokentype type);

#endif