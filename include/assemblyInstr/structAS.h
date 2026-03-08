#ifndef STRUCTAS_H
#define STRUCTAS_H

typedef struct {
    int offset;
    char* name_var;
} StackVar;

typedef struct {
    int count;
    int current_offset_count;
    int tmp[256];
    StackVar var[256];
}StackLayout;

#endif