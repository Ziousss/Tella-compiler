#include "../include/assemblyInstr/assemblyInstrHeader.h"

StackLayout *stackFunctionAS(IRstruct *IRlist, FILE *output, ASContext* context){
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
    char *funcName = tmp->data.function.name_func;

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
            case IR_LESSEQ: {
                Operand dst = tmp->data.binary.dst;
                Operand src1 = tmp->data.binary.src1;
                Operand src2 = tmp->data.binary.src2;

                //check if null in the function itself
                setStackLayout(dst, stack, context);
                setStackLayout(src1, stack, context);
                setStackLayout(src2, stack, context);
                break;
            }
            case IR_ASSIGN: {
                Operand dst = tmp->data.assign.dst;
                Operand src1 = tmp->data.assign.src;

                setStackLayout(dst, stack, context);
                setStackLayout(src1, stack, context);
                break;
            }
            case IR_ASSIGN_ARR: {
                Operand value = tmp->data.assignArray.value;
                Operand base = tmp->data.assignArray.base;
                Operand index = tmp->data.assignArray.index;

                setStackLayout(value, stack, context);
                setStackLayout(index, stack, context);
                setStackLayout(base, stack, context);
                break; 
            }
            case IR_JMP_FALSE:{
                Operand condition = tmp->data.condition_jump.condition;
                setStackLayout(condition, stack, context);

                break;
            }
            case IR_CALL:{
                Operand call = tmp->data.call.dst;
                setStackLayout(call, stack, context);

                break;
            }
            case IR_RET:{
                Operand ret = tmp->data.ret.return_value;
                setStackLayout(ret, stack, context);

                break;
            }
            case IR_ARG: {
                Operand arg = tmp->data.arg.value;
                setStackLayout(arg, stack, context);

                break;
            }
            case IR_PARAM: {
                Operand param = tmp->data.parameters.parameter;
                setParamStack(param, stack, param_offset);
                param_offset += 8;

                break;
            }
            case IR_LABEL: break;
            case IR_JMP: break;

            //array already allocated
            case IR_LOAD_ARRAY: {
                Operand dst = tmp->data.loadArray.base;
                Operand index = tmp->data.loadArray.index;
                Operand base = tmp->data.loadArray.base;

                setStackLayout(base, stack, context);
                setStackLayout(dst, stack, context);
                setStackLayout(index, stack , context);

                break;
            }

            default: {
                printf("Unknown IR token in stackFunctionAS %d.\n", tmp->op);
                context->errors++;
                break;
            }
        }
        tmp = tmp->next;
    }

    fprintf(output, "%s:\n", funcName);
    fprintf(output, "push rbp\n");
    fprintf(output, "mov rbp, rsp\n");
    if(stack->current_offset_count%16 == 0){
        fprintf(output, "sub rsp, %d\n", -stack->current_offset_count);
    } else {
        fprintf(output, "sub rsp, %d\n", -stack->current_offset_count-8);
    }
    return stack;
}