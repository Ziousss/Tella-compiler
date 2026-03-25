#ifndef HERLPERFUNCAS_H
#define HERLPERFUNCAS_H

#include "structAS.h"
#include "../include/IntermediateRep/IRheader.h"

void setStackLayout(Operand op, StackLayout *stack, ASContext* context);
void setVarStack(Operand op, StackLayout *stack);
void setTmpStack(Operand op, StackLayout *stack);
void setParamStack(Operand param, StackLayout *stack, int param_offset);
int findVarInStack(Operand op, StackLayout *stack);
int getOffset(Operand op, StackLayout *stack, ASContext* context);
void movConstant(Operand op, FILE *output, const char *reg, ASContext* context);
void setArrStack(Operand op, StackLayout *stack);
void freeStackLayout(StackLayout *stack);


#endif