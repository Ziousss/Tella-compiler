#ifndef ASSEMBLYINSTRHEADER_H
#define ASSEMBLYINSTRHEADER_H

#include "../include/IntermediateRep/IRheader.h"
#include "helperFuncAS.h"


bool assemblyInstr(IRstruct *IRlist);
void binaryAS(IRstruct *binary, FILE *output);
void programAS(IRstruct *IRlist, FILE *output);
StackLayout *functionsAS(IRstruct *IRlist);

#endif