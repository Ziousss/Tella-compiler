#ifndef STRUCTIR_H
#define STRUCTIR_H

#include <stdbool.h>
#include "../include/semanticAnalyser/struct.h"

typedef struct Operand Operand;
typedef struct IRstruct IRstruct;

typedef enum {
    IR_LABEL, IR_FUNC, IR_RODATA,
    IR_ADD, IR_SUB, IR_MULT, IR_DIV, IR_GR, IR_GREQ, IR_LESS, IR_LESSEQ, IR_EQEQ, IR_UNEQ, 
    IR_CALL, IR_JMP, IR_JMP_FALSE, IR_RET, IR_ASSIGN, IR_ARG, IR_PARAM, 
    IR_ASSIGN_ARR, IR_LOAD_ARRAY,
    IR_ERROR,
} IRoperation;

typedef enum {
    IR_VAR, IR_CONST, IR_TMP, IR_VOID_OPERAND, IR_IRTYPE_ERROR, IR_ARR, IR_OPERAND_ERROR
} IRtype;

typedef enum {
    IR_INT, IR_STRING, IR_CHAR, IR_BOOL, IR_VOID, IR_CST_ERROR, IR_SIZET
} CstTypes;

typedef struct Operand {
    IRtype IR_type;

    union {
        struct {
            char *identifier;
            CstTypes Type;

            //Only for parameters in IR.
            CstTypes paramType;
            int param_index;

            //Only for array
            int size;
            int elementSize;
        } IR_Variable;
        
        struct {
            CstTypes cst_type;
            union {
                int stringID;
                int number;
                char chr;
                bool boolean;
            }value;
        } IR_constant;

        struct {
            CstTypes type;
            int id_tmp;
        } IR_tmp;        
    }data; 
} Operand;


typedef struct IRstruct {
    IRoperation op;
    union {
        struct {
            int stringID;
            char *string;
        } rodata;
        
        struct {
            Operand dst, src1, src2;
        } binary;

        struct {
            int label_id;
        } label;
        
        struct {
            int target_label;
        } jump;

        struct {
            Operand dst;
            Operand src;
        } assign;

        struct {
            int target_label;
            Operand condition;
        } condition_jump;
        
        struct {
            CstTypes type;
            Operand return_value;
        } ret;

        struct {
            char *func_name;
            int arg_count;
            Operand dst;
        } call;

        struct {
            Operand value;
        } arg;

        struct {
            char *name_func;
        } function;

        struct {
            Operand parameter;
        } parameters;     
        
        //For arrays specifically
        struct {
            Operand dst;
            Operand base;
            Operand index;
            bool isPointer;
        } loadArray;

        struct {
            Operand base;
            Operand index;
            Operand value;
        } assignArray;
        
    } data;

    struct IRstruct *next;
} IRstruct;

//Instead of passing every one of those in each function and having 6 arguments, I only pass one struct.
typedef struct {
    IRstruct *head;
    IRstruct *tail;
    int current_tmp;
    int current_label;
    int current_string;
    int errors;
    bool returned;
    IRsymbole *IRsym;
} IRContext;

#endif