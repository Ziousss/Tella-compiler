#ifndef ASSEMBLYINSTRHEADER_H
#define ASSEMBLYINSTRHEADER_H

#include "../include/IntermediateRep/IRheader.h"
#include "helperFuncAS.h"

bool mainAssemblyInstr(IRstruct *IRlist);
void binaryAS(IRstruct *binary, FILE *output, StackLayout *stack);
void programAS(IRstruct *IRlist, FILE *output);
StackLayout *stackFunctionAS(IRstruct *IRlist, FILE *output);
void callAS(IRstruct *call, FILE *output, StackLayout *stack);
void argAS(IRstruct *arg, FILE *output, StackLayout *stack);
void returnAS(IRstruct *ret, FILE *output, StackLayout *stack);
void condJumpAS(IRstruct *call, FILE *output, StackLayout *stack);
void assignAS(IRstruct *assign, FILE *output, StackLayout *stack);
void paramAS(IRstruct *parameter, FILE *output, StackLayout *stack);

#endif