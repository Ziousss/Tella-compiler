#ifndef ASSEMBLYINSTRHEADER_H
#define ASSEMBLYINSTRHEADER_H

#include "../include/IntermediateRep/IRheader.h"
#include "helperFuncAS.h"

int mainAssemblyInstr(IRstruct *IRlist, bool stackLayoutBool);
void binaryAS(IRstruct *binary, FILE *output, StackLayout *stack, ASContext* context);
void programAS(IRstruct *IRlist, FILE *output, ASContext* context, bool stackLayoutBool);
StackLayout *stackFunctionAS(IRstruct *IRlist, FILE *outpu, ASContext* contextt);
void callAS(IRstruct *call, FILE *output, StackLayout *stack, ASContext* context);
void argAS(IRstruct *arg, FILE *output, StackLayout *stack, ASContext* context);
void returnAS(IRstruct *ret, FILE *output, StackLayout *stack, ASContext* context);
void condJumpAS(IRstruct *call, FILE *output, StackLayout *stack, ASContext* context);
void assignAS(IRstruct *assign, FILE *output, StackLayout *stack, ASContext* context);
void paramAS(IRstruct *parameter, FILE *output, StackLayout *stack, ASContext* context);
void ifStmtAS(IRstruct *ifStmt, FILE *output, StackLayout *stack, ASContext* context);
void assignArrAS(IRstruct *assignArr, FILE *output, StackLayout *stack, ASContext* context);
void loadArrAS(IRstruct *loadArr, FILE *output, StackLayout *stack, ASContext *context);

#endif