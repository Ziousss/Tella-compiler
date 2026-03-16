#ifndef ASSEMBLYINSTRHEADER_H
#define ASSEMBLYINSTRHEADER_H

#include "../include/IntermediateRep/IRheader.h"
#include "helperFuncAS.h"


bool assemblyInstr(IRstruct *IRlist);
void binaryAS(IRstruct *binary, FILE *output, StackLayout *stack);
void programAS(IRstruct *IRlist, FILE *output);
StackLayout *stackFunctionAS(IRstruct *IRlist);
void callAS(IRstruct *call, FILE *output, StackLayout *stack);
void argAS(IRstruct *arg, FILE *output, StackLayout *stack);
void returnAS(IRstruct *ret, FILE *output, StackLayout *stack);

#endif