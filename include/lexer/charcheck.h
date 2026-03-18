#ifndef CHARCHECK_H
#define CHARCHECK_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool isDelimiter (char chr);
bool isOperation (char chr);
bool validIdentitfier (char *str);
bool isKeyword (char *str);
bool isInteger (char *str);
char* getSubstring (char *str, size_t start, size_t end);
bool specialCaseDelimiter (char chr);
bool whiteSpace(char chr);
bool notAccepted (char chr);

#endif