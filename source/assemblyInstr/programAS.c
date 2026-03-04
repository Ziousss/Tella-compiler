#include "../include/machineCode/machineCodeHeader.h"

void programMC(IRstruct *IRlist, FILE *output){
    IRstruct *tmp = IRlist;
    while(tmp != NULL){
        IRoperation op = tmp->op;
        switch (op) {
            case IR_LABEL:
                labelMC(IRlist->data.label, output);
                break;

            case IR_JMP: 
                jumpMC(IRlist->data.jump, output);
                break;
            
            case IR_JMP_FALSE: 
                condJumpMC(IRlist->data.condition_jump, output);
                break;
            
            case IR_RET: 
                returnMC(IRlist->data.ret, output);
                break;
            
            case IR_ADD:
            case IR_SUB:
            case IR_MULT:
            case IR_DIV:
            case IR_EQEQ:
            case IR_UNEQ:
            case IR_GR:
            case IR_GREQ:
            case IR_LESS:
            case IR_LESSEQ:
                binaryMC(IRlist->data.binary, output);
                break;
        }

        tmp = tmp->next;
    }
}