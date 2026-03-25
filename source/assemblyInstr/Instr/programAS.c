#include "../include/assemblyInstr/assemblyInstrHeader.h"

void programAS(IRstruct *IRlist, FILE *output, ASContext* context){
    IRstruct *tmp = IRlist;  
    StackLayout *stack;

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
                condJumpAS(tmp, output, stack, context);
                break;
            
            case IR_RET: 
                returnAS(tmp, output, stack, context);
                break;

            case IR_CALL:
                callAS(tmp, output, stack, context);
                break;

            case IR_ASSIGN:
                assignAS(tmp, output, stack, context);
                break;

            case IR_ARG:
                argAS(tmp, output, stack, context);
                break;

            case IR_PARAM:
                paramAS(tmp, output, stack, context);
                break;
            
            case IR_ASSIGN_ARR:
                assignArrAS(tmp, output, stack, context);
                break;

            case IR_SUB:
            case IR_ADD:
            case IR_MULT:
            case IR_DIV:
            case IR_EQEQ:
            case IR_UNEQ:
            case IR_GR:
            case IR_GREQ:
            case IR_LESS:
            case IR_LESSEQ:
                binaryAS(tmp, output, stack, context);
                break;
            
            case IR_FUNC:
                stack = stackFunctionAS(tmp, output, context);
                if(stack == NULL){
                    return;
                }
                break;
        
            case IR_LOAD_ARRAY:
                loadArrAS(tmp, output, stack, context);
                break;

            default:
                printf("Unhandled op in stackFunctionAS: %d\n", tmp->op);
                context->errors++;
                break;
        }
        tmp = tmp->next;
    }

    free(stack);
}