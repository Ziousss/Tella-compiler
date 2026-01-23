#ifndef HELPERFUNCIR_H
#define HELPERFUNCIR_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "structIR.h"
#include "../include/lexer/tokenizer.h"

void emit(IRstruct *to_add, IRContext *context);
IRstruct *newLabel(IRContext *context);
IRstruct *newBinary(IRContext *context, Operand dst, Operand src1, Operand src2, IRoperation op);
IRstruct *newJmp(IRContext *context, int target);
IRstruct *newReturn(IRContext *context, Operand target);
IRstruct *newAssign(IRContext *context, Operand dst, Operand src);
Operand newString(char *value);
Operand newChar(char value);
Operand newBool(bool value);
Operand newInt(int value);
Operand newTmp(IRContext *context);
IRoperation fromTokToIRtype(Tokentype type);

#endif