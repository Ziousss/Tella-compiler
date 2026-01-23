#ifndef IRHEADER_H
#define IRHEADER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "structIR.h"
#include "../include/parser/ast.h"
#include "helperFuncIR.h"
#include "helperFunc.h"

IRstruct *programIR(ASTnode *program);
void funcDefIR(ASTnode *funcdef, IRContext *context);
void blockIR(ASTnode *block, IRContext *context);
Operand expressionIR(ASTnode *expression, IRContext *context);

#endif