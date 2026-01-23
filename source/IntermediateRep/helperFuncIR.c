#include "../include/IntermediateRep/helperFuncIR.h"

void emit(IRstruct *to_add, IRContext *context){
    to_add->next = NULL;

    if(context->head == NULL){
        context->head = to_add;
        context->tail = to_add;
        return;
    }

    context->tail->next = to_add;
    context->tail = to_add;
}

IRstruct *newLabel(IRContext *context){
    IRstruct *new = malloc(sizeof(IRstruct));
    if(new == NULL){
        printf("Malloc error in newLabel with number %d.\n", context->current_label+1);
        context->errors++;
        return NULL;
    }

    new->next = NULL;
    new->op = IR_LABEL;
    new->data.label.label_id = context->current_label++;

    return new;
}

IRstruct *newBinary(IRContext *context, Operand *dst, Operand *src1, Operand *src2, IRoperation op){
    IRstruct *new = malloc(sizeof(IRstruct));
    if(new == NULL){
        printf("Malloc error in newBinary.\n");
        context->errors++;
        return NULL;
    }

    new->next = NULL;
    new->op = op;
    new->data.binary.dst = dst;
    new->data.binary.src1 = src1;
    new->data.binary.src2 = src2;

    return new;
}

IRstruct *newJmp(IRContext *context, int target){
    IRstruct *new = malloc(sizeof(IRstruct));
    if(new == NULL){
        printf("Malloc error in newJmp to taget %d.\n", target);
        context->errors++;
        return NULL;
    }

    new->next = NULL;
    new->op = IR_JMP;
    new->data.jump.target_label = target;

    return new;
}

IRstruct *newReturn(IRContext *context, Operand *target){
    IRstruct *new = malloc(sizeof(IRstruct));
    if(new == NULL){
        printf("Malloc error in newReturn to taget %d.\n", target);
        context->errors++;
        return NULL;
    }

    new->next = NULL;
    new->op = IR_RET;
    new->data.ret.return_value = target;

    return new;
}