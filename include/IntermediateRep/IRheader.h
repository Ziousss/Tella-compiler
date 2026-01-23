#ifndef IRHEADER_H
#define IRHEADER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "structIR.h"
#include "helperFunc.h"

IRstruct *programIR(ASTnode *program);
void funcDefIR(ASTnode *funcdef, IRContext *context);
void blockIR(ASTnode *block, IRContext *context);

#endif