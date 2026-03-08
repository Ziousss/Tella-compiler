#include "../include/assemblyInstr/assemblyInstrHeader.h"

void programAS(IRstruct *IRlist, FILE *output){
    IRstruct *tmp = IRlist;
    StackLayout *stack = functionsAS(IRlist);
    if(stack == NULL){
        return;
    }
    
    while(tmp != NULL){
        IRoperation op = tmp->op;
        switch (op) {
            case IR_LABEL:
                fprintf(output, "L%d:\n", tmp->data.label.label_id);
                break;

            case IR_JMP: 
                fprintf(output, "jmp L%d\n", tmp->data.jump.target_label);
                break;
            
            case IR_JMP_FALSE: 
                condJumpAS(tmp->data.condition_jump, output);
                break;
            
            case IR_RET: 
                returnAS(tmp->data.ret, output);
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
                binaryAS(tmp, output);
                break;
        }

        tmp = tmp->next;
    }
}