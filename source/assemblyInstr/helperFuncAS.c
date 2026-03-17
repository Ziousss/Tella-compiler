#include "../include/assemblyInstr/helperFuncAS.h"

void setStackLayout(Operand op, StackLayout *stack){
    if(op.IR_type == IR_CONST){
        return;
    } 
    else if (op.IR_type == IR_VAR) {
        setVarStack(op, stack);
        return;
    } 
    else if(op.IR_type == IR_TMP) {
        setTmpStack(op,stack);
        return;
    } else {
        printf("Problem in setStackLayout.\n");
        fflush(stdout);
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
    if(stack->tmp[op.data.IR_tmp.id_tmp] != -1){
        return;
    }
    stack->current_offset_count -= 8;
    stack->tmp[op.data.IR_tmp.id_tmp] = stack->current_offset_count;
}

void setParamStack(Operand param, StackLayout *stack, int param_offset){
    stack->arg[stack->param_count].name_var = param.data.IR_Variable.identifier;
    stack->arg[stack->param_count++].offset = param_offset;
}

int findVarInStack(Operand op, StackLayout *stack){
    for(int i = 0; i < stack->var_count; i++){
        if(strcmp(op.data.IR_Variable.identifier, stack->var[i].name_var) == 0){
            return stack->var[i].offset;
        }
    }

    for(int i = 0; i < stack->param_count; i++){
        if(strcmp(op.data.IR_Variable.identifier, stack->arg[i].name_var) == 0){
            return stack->arg[i].offset;
        }
    }

    return -1;
}

int getOffset(Operand op, StackLayout *stack){
    switch (op.IR_type) {
        case IR_VAR:
            int offset = findVarInStack(op, stack);
            if(offset == -1){
                printf("Variable not found in stack\n");
            }
            return offset;

        case IR_TMP:
            int tmpOffset = stack->tmp[op.data.IR_tmp.id_tmp];
            if(tmpOffset == -1){
                printf("Temporary not found in stack\n");
            }
            return tmpOffset;

        default:
            printf("No offset found for var or tmp.\n");
            return 0;
    }
}

void movConstant(Operand op, FILE *output, char *reg){
    IRtype type = op.IR_type;
    if(type != IR_CONST){
        printf("Wrong Operand given to movConstant.\n");
        return;
    }

    CstTypes cst = op.data.IR_constant.cst_type;
    switch (cst) {
    case IR_INT:
        fprintf(output, "mov %s, %d\n", reg, op.data.IR_constant.value.number);
        break;

    case IR_CHAR:
        fprintf(output, "mov %s, %c\n", reg, op.data.IR_constant.value.chr);
        break;

    case IR_BOOL:
        fprintf(output, "mov %s, %d\n", reg, op.data.IR_constant.value.boolean);
        break;

    case IR_STRING:
        printf("String constants not yet implemented\n");
        break;
    
    default:
        printf("Unknown cst type given to movConstant.\n");
        break;
    }
}