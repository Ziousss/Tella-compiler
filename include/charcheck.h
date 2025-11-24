#ifndef CHARCHECK_H
#define CHARCHECK_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool isDelimiter (char chr);
bool isOperation (char chr);
bool validIdentitfier (char chr);
bool isKeyword (char *str);
bool isInteger (char *str);
char* getSubstring (char *str, int start, int end) ;

#endif