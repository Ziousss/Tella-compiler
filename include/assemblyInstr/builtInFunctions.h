#ifndef BUILTINFUNCTIONS_H
#define BUILTINFUNCTIONS_H

#include <stdio.h>
#include <stdbool.h>

#include "helperFuncAS.h"
#include "structAS.h"

void tellaPutChar(FILE *output, StackLayout *stack, ASContext *context);
void tellaPrint(FILE *output, ASContext *context);

#endif