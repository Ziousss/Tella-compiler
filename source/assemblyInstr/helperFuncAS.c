#include "../include/assemblyInstr/helperFuncAS.h"

void setStackLayout(Operand op, StackLayout *stack){
    if(op.IR_type == 0){
        return;
    }

    if(op.IR_type == IR_CONST){
        return;
    } 
    else if (op.IR_type == IR_VAR) {
        setVarStack(op, stack);
        return;
    } 
    else {
        setTmpStack(op,stack);
        return;
    }
}

void setVarStack(Operand op, StackLayout *stack){
    for(int i = 0; i < stack->var_count; i++){
        if(strcmp(op.data.IR_Variable.identifier, stack->var[i].name_var) == 0){
            return;
        }
    }

    stack->current_offset_count -= 8;
    stack->var[stack->var_count].name_var = op.data.IR_Variable.identifier;
    stack->var[stack->var_count++].offset = stack->current_offset_count;
}

void setTmpStack(Operand op, StackLayout *stack){   
    if(stack->tmp[op.data.IR_tmp.id_tmp] == -1){
        return;
    }
    stack->current_offset_count -= 8;
    stack->tmp[op.data.IR_tmp.id_tmp] = stack->current_offset_count;
}

void setParamstack(Operand param, StackLayout *stack, int param_offset){
    stack->var[stack->param_count].name_var = param.data.IR_Variable.identifier;
    stack->var[stack->param_count++].offset = param_offset;
}

int findVarInStack(Operand op, StackLayout *stack){
    for(int i = 0; i < stack->var_count; i++){
        if(strcmp(op.data.IR_Variable.identifier, stack->var[i].name_var) == 0){
            return stack->var->offset;
        }
    }
}

int getOffset(Operand op, StackLayout *stack){
    switch (op.IR_type) {
        case IR_VAR:
            return findVarInStack(op, stack);
        case IR_TMP:
            return stack->tmp[op.data.IR_tmp.id_tmp];
        default:
            printf("No offset found for var or tmp.\n");
            return 0;
    }
}