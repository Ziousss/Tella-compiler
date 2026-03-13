#include "../include/assemblyInstr/assemblyInstrHeader.h"

StackLayout *stackFunctionAS(IRstruct *IRlist){
    IRstruct *tmp = IRlist;
    if(tmp->op != IR_FUNC){
        printf("Wrong token given to functionAS.\n");
        return NULL;
    }

    StackLayout *stack = malloc(sizeof(StackLayout));
    if(stack == NULL){
        printf("StackLayout failed to malloc.\n");
        return NULL;
    }
    stack->var_count = 0;
    stack->param_count = 0;
    stack->current_offset_count = 0;

    //since param are at + from rbp
    int param_offset = 8;
    
    for(int i = 0; i < 256; i++){
        stack->tmp[i] = -1;
        stack->var[i].offset = 0;
        stack->var[i].name_var = NULL;
    }

    tmp = tmp->next;
    while(tmp != NULL && tmp->op != IR_FUNC){
        switch(tmp->op){
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
            case IR_ASSIGN: {
                Operand dst = tmp->data.binary.dst;
                Operand src1 = tmp->data.binary.src1;
                Operand src2 = tmp->data.binary.src2;

                //check if null in the function itself
                setStackLayout(dst, stack);
                setStackLayout(src1, stack);
                setStackLayout(src2, stack);
                break;
            }
            case IR_JMP_FALSE:{
                Operand condition = tmp->data.condition_jump.condition;
                setStackLayout(condition, stack);

                break;
            }
            case IR_CALL:{
                Operand call = tmp->data.call.dst;
                setStackLayout(call, stack);

                break;
            }
            case IR_RET:{
                Operand ret = tmp->data.ret.return_value;
                setStackLayout(ret, stack);

                break;
            }
            case IR_ARG: {
                Operand arg = tmp->data.arg.value;
                setStackLayout(arg, stack);

                break;
            }
            case IR_PARAM: {
                Operand param = tmp->data.parameters.parameter;
                setParamStack(param, stack, param_offset);
                param_offset += 8;

                break;
            }
        }
        tmp = tmp->next;
    }

    return stack;
}