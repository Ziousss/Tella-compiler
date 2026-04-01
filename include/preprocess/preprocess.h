#ifndef PREPROCESS_H
#define PREPROCESS_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../include/lexer/readFile.h"

typedef struct SourceChar SourceChar;
typedef struct PreResult PreResult;

typedef struct SourceChar{
    char c;
    size_t line;
    const char *fileName;
} SourceChar;

typedef struct PreResult{
    SourceChar *data;
    size_t size;
} PreResult;

PreResult preprocess(char *source, char *fileName);

#endif