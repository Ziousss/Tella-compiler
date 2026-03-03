#ifndef IRHEADER_H
#define IRHEADER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "structIR.h"
#include "../include/parser/ast.h"
#include "helperFuncIR.h"
#include "../include/parser/helperFunc.h"
#include "../include/semanticAnalyser/struct.h"
#include "printIR.h"

IRstruct *programIR(ASTnode *program, GlobalFunc *definedFunc);
void funcDefIR(ASTnode *funcdef, IRContext *context);
void blockIR(ASTnode *block, IRContext *context);
Operand expressionIR(ASTnode *expression, IRContext *context);
void forIR(ASTnode *forStmt, IRContext *context);
void whileIR(ASTnode *whileStmt, IRContext *context);
void returnIR(ASTnode *returnNode, IRContext *context);
Operand funcCallIR(ASTnode *funcCall, IRContext *context);
void ifStmtIR(ASTnode *ifStmt, IRContext *context);

#endif