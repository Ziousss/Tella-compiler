#ifndef PRINTIR_H
#define PRINTIR_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "structIR.h"
#include "../include/lexer/tokenizer.h"
#include "../include/semanticAnalyser/struct.h"
#include "helperFuncIR.h"

void printIR(IRstruct *IR);
void printOperand(Operand toPrint);

#endif