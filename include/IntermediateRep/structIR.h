#ifndef STRUCTIR_H
#define STRUCTIR_H

#include <stdbool.h>

typedef struct Operand Operand;
typedef struct IRstruct IRstruct;

typedef enum {
    IR_LABEL, IR_FUNC,
    IR_ADD, IR_SUB, IR_MULT, IR_DIV, IR_GR, IR_GREQ, IR_LESS, IR_LESSEQ, IR_EQEQ, IR_UNEQ, 
    IR_CALL, IR_JMP, IR_JMP_FALSE, IR_RET, IR_ASSIGN, IR_ARG,
    IR_ERROR,
} IRoperation;

typedef enum {
    IR_VAR, IR_CONST, IR_TMP, 
} IRtype;

typedef enum {
    IR_INT, IR_STRING, IR_CHAR, IR_BOOL, IR_VOID
} CstTypes;

typedef struct Operand {
    IRtype IR_type;

    //for returns etc to know if void or not
    bool ret_void;
    union {
        struct {
            char *identifier;
        } IR_Variable;
        
        struct {
            CstTypes cst_type;
            union {
                struct {
                    char *string;
                }string;

                struct {
                    int number;
                }number;

                struct {
                    char chr;
                }chr;

                struct {
                    bool boolean;
                }boolean;

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
            Operand dst, src1, src2;
        } binary;

        struct {
            int label_id;
        } label;
        
        struct {
            int target_label;
        } jump;
        
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
    } data;
    struct IRstruct *next;
} IRstruct;

//Instead of passing every one of those in each function and having 6 arguments, I only pass one struct.
typedef struct {
    IRstruct *head;
    IRstruct *tail;
    int current_tmp;
    int current_label;
    int errors;
    bool returned;
} IRContext;

#endif