#ifndef HELPERFUNCIR_H
#define HELPERFUNCIR_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "structIR.h"
#include "../include/lexer/tokenizer.h"
#include "../include/semanticAnalyser/struct.h"
#include "../include/parser/ast.h"

void emit(IRstruct *to_add, IRContext *context);
IRstruct *newLabel(IRContext *context, int label);
IRstruct *newFunc(IRContext *context, char *name_func);
IRstruct *newBinary(IRContext *context, Operand dst, Operand src1, Operand src2, IRoperation op);
IRstruct *newJmp(IRContext *context, int target);
IRstruct *newReturn(IRContext *context, Operand target);
IRstruct *newAssign(IRContext *context, Operand dst, Operand src);
Operand newString(int stringID);
Operand newChar(char value);
Operand newBool(bool value);
Operand newInt(int value);
Operand newTmp(CstTypes type, IRContext *context);
IRoperation fromTokToIRtype(Tokentype type);
IRstruct *newJmpFalse(IRContext *context, int end_label, Operand condition);
void initGlobalFunctions(GlobalFunc *funcs);
GlobalFunc *findFuncDef(char *name);
CstTypes fromSemToIRTypes(SemanticType type);
IRstruct *newArg(IRContext *context, Operand arg);
IRstruct *newCall(IRContext *context, char *name, int count, Operand dst);
const char *printCstType(CstTypes type);
bool isbool(IRoperation op);
IRstruct *newParam(IRContext *context, int index, char *name, CstTypes type);
CstTypes fromTokToCstType(Tokentype type);
int getSizeElement(SemanticType type);
IRstruct *newAssignArray(IRContext *context, Operand base, Operand value, Operand index);
IRstruct *newArrayLoad(IRContext *context, Operand base, Operand index, Operand tmp, bool isChar);
IRsymbole *findDecl(char *name, IRContext *context);

#endif