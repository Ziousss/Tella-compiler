#ifndef STRUCTIR_H
#define STRUCTIR_H

#include <stdbool.h>

typedef struct Operand Operand;
typedef struct IRstruct IRstruct;

typedef enum {
    IR_LABEL,
    IR_ADD, IR_SUB, IR_MULT, IR_DIV,
    IR_CALL, IR_JMP, IR_RET, IR_ASSIGN, 
    IR_ERROR,
} IRoperation;

typedef enum {
    IR_VAR, IR_CONST, IR_TMP
} IRtype;

typedef enum {
    IR_INT, IR_STRING, IR_CHAR, IR_BOOL
} CstTypes;

typedef struct {
    IRtype IR_type;
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
            Operand return_value;
        } ret;
    } data;
    struct IRstruct *next;
} IRstruct;

//Instead of passing everyone of those in each function and having 5 arguments, I only pass one struct.
typedef struct {
    IRstruct *head;
    IRstruct *tail;
    int current_tmp;
    int current_label;
    int errors;
} IRContext;

#endif