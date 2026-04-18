#include "../include/IntermediateRep/IRheader.h"

Operand rodataIR(ASTnode *expression, IRContext *context){
    char *stringChar = expression->data.string_literal.string;

    IRstruct *stringIR = malloc(sizeof(IRstruct));
    if(stringIR == NULL){
        printf("Malloc failed in rodataIR.\n");
        context->errors++;
        Operand error;
        error.IR_type = IR_OPERAND_ERROR;
        return error;
    }

    int stringID = context->current_string++;

    stringIR->op = IR_RODATA;
    stringIR->data.rodata.string = strdup(stringChar);
    stringIR->data.rodata.stringID = stringID;
    stringIR->next = NULL;

    emit(stringIR, context);

    Operand stringOP;
    stringOP.IR_type = IR_CONST;
    stringOP.data.IR_constant.cst_type = IR_STRING;
    stringOP.data.IR_constant.value.stringID = stringID;
    return stringOP;
}