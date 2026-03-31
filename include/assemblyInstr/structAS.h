#ifndef STRUCTAS_H
#define STRUCTAS_H

#include "../include/IntermediateRep/structIR.h"

typedef struct {
    int offset;
    char* name_var;
} StackVar;

typedef struct {
    int var_count;
    int param_count;
    int current_offset_count;
    int tmp[256];
    StackVar var[256];
    StackVar arg[256];
    int arg_count;
}StackLayout;

typedef struct{
    int offset[6];
    IRtype argType[6];
    int stringID[6];

    IRstruct *rodata;

    int errors;
} ASContext;

#endif