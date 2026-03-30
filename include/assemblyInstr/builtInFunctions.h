#ifndef BUILTINFUNCTIONS_H
#define BUILTINFUNCTIONS_H

#include <stdio.h>
#include <stdbool.h>

#include "structAS.h"

void tellaPutChar(FILE *output, StackLayout *stack, ASContext *context);
void tellaPrint(char *string, FILE *output, StackLayout *stack, ASContext *context);

#endif