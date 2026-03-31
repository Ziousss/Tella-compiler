#include "../include/assemblyInstr/helperFuncAS.h"

void setStackLayout(Operand op, StackLayout *stack, ASContext* context){
    if(op.IR_type == IR_CONST){
        return;
    } 
    else if (op.IR_type == IR_VAR) {
        setVarStack(op, stack);
        return;
    } 
    else if(op.IR_type == IR_ARR){
        setArrStack(op, stack);
        return;
    }
    else if(op.IR_type == IR_TMP) {
        setTmpStack(op,stack);
        return;
    } else if(IR_VOID_OPERAND){
        return;
    } else {
        printf("IRtype problem in setStackLayout {%d}.\n", op.IR_type);
        context->errors++;
        fflush(stdout);
        return;
    }
}

void setArrStack(Operand op, StackLayout *stack){
    for(int i = 0; i < stack->var_count; i++){
        if(strcmp(op.data.IR_Variable.identifier, stack->var[i].name_var) == 0){
            return;
        }
    }

    for(int i = 0; i < stack->arg_count; i++){
        if(strcmp(op.data.IR_Variable.identifier, stack->arg[i].name_var) == 0){
            return;
        }
    }

    if(op.data.IR_Variable.size > 0){
        printOperand(op);
        int size = op.data.IR_Variable.size;
        int elementSize = op.data.IR_Variable.elementSize;
        int spaceNeeded = size * elementSize;
        while(spaceNeeded % 8 != 0){
            spaceNeeded++;
        }

        if(spaceNeeded == 0){
            printf("Warning: SpaceNeeded for array %s was 0 ? UB.\n", op.data.IR_Variable.identifier);
            return;
        }

        stack->current_offset_count -= spaceNeeded;
    } else {
        stack->current_offset_count -= 8;
    }

    stack->var[stack->var_count].name_var = strdup(op.data.IR_Variable.identifier);
    stack->var[stack->var_count++].offset = stack->current_offset_count;
}

void setVarStack(Operand op, StackLayout *stack){
    for(int i = 0; i < stack->param_count; i++){
        if(strcmp(op.data.IR_Variable.identifier, stack->arg[i].name_var) == 0){
            return;
        }
    }

    for(int i = 0; i < stack->var_count; i++){
        if(strcmp(op.data.IR_Variable.identifier, stack->var[i].name_var) == 0){
            return;
        }
    }

    stack->current_offset_count -= 8;
    stack->var[stack->var_count].name_var = strdup(op.data.IR_Variable.identifier);
    stack->var[stack->var_count++].offset = stack->current_offset_count;
}

void setTmpStack(Operand op, StackLayout *stack){   
    if(stack->tmp[op.data.IR_tmp.id_tmp] != -1){
        return;
    }
    stack->current_offset_count -= 8;
    stack->tmp[op.data.IR_tmp.id_tmp] = stack->current_offset_count;
}

//Useless now Since everything on the stack
void setParamStack(Operand param, StackLayout *stack, int param_offset){
    stack->arg[stack->param_count].name_var = strdup(param.data.IR_Variable.identifier);
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

int getOffset(Operand op, StackLayout *stack, ASContext* context){
    switch (op.IR_type) {
        case IR_ARR:
        case IR_VAR:{
            int offset = findVarInStack(op, stack);
            if(offset == -1){
                printf("Variable not found in stack\n");
                context->errors++;
            }
            return offset;
        }

        case IR_TMP:{
            int tmpOffset = stack->tmp[op.data.IR_tmp.id_tmp];
            if(tmpOffset == -1){
                printf("Temporary not found in stack\n");
                context->errors++;
            }
            return tmpOffset;
        }

        default:{
            printf("No offset found for var or tmp.\n");
            context->errors++;
            return 0;
        }
    }
}

void movConstant(Operand op, FILE *output, const char *reg, ASContext* context){
    IRtype type = op.IR_type;
    if(type != IR_CONST){
        printf("Wrong Operand given to movConstant.\n");
        context->errors++;
        return;
    }

    CstTypes cst = op.data.IR_constant.cst_type;
    switch (cst) {
        case IR_INT:{
            fprintf(output, "mov %s, %d\n", reg, op.data.IR_constant.value.number);
            break;
        }

        case IR_CHAR:{
            fprintf(output, "mov %s, %d\n", reg, op.data.IR_constant.value.chr);
            break;
        }

        case IR_BOOL:{
            fprintf(output, "mov %s, %d\n", reg, op.data.IR_constant.value.boolean);
            break;
        }

        case IR_STRING:{
            fprintf(output, "lea %s, [rip + string_%d]\n", reg, op.data.IR_constant.value.stringID);
            break;
        }

        default:{
            printf("Unknown cst type given to movConstant.\n");
            context->errors++;
            break;
        }
    }
}

void freeStackLayout(StackLayout *stack){
    if(stack == NULL) return;

    for(int i = 0; i < stack->var_count; i++){
        if(stack->var[i].name_var != NULL){
            free(stack->var[i].name_var);
        }
    }
    free(stack);
}

void printStackLayout(StackLayout *stack, char *nameFunc){
    printf("\n========== STACK LAYOUT %s ==========\n", nameFunc);
    
    printf("Total offset count: %d (allocating %d bytes)\n", 
           stack->current_offset_count, -stack->current_offset_count);
    printf("\n--- LOCAL VARIABLES ---\n");
    
    if(stack->var_count == 0){
        printf("  (none)\n");
    } else {
        for(int i = 0; i < stack->var_count; i++){
            printf("  %d. %s @ [rbp %+d]\n", 
                   i+1, 
                   stack->var[i].name_var, 
                   stack->var[i].offset);
        }
    }
    
    printf("\n--- TEMPORARIES ---\n");
    int tmp_count = 0;
    for(int i = 0; i < 256; i++){
        if(stack->tmp[i] != -1){
            printf("  t%d @ [rbp %+d]\n", i, stack->tmp[i]);
            tmp_count++;
        }
    }
    if(tmp_count == 0){
        printf("  (none)\n");
    }
    
    printf("\n--- PARAMETERS ---\n");
    if(stack->param_count == 0){
        printf("  (none)\n");
    } else {
        for(int i = 0; i < stack->param_count; i++){
            printf("  %d. %s @ [rbp %+d]\n", 
                   i+1, 
                   stack->arg[i].name_var, 
                   stack->arg[i].offset);
        }
    }
    
    printf("\n========== END STACK LAYOUT ==========\n\n");
}

void builtInFunctions(FILE *output, char *nameFunc, StackLayout *stack, ASContext *context){
    if(strcmp(nameFunc, "tellaPutChar") == 0){
        tellaPutChar(output, stack, context);
    } else if(strcmp(nameFunc, "tellaPrint") == 0){
        tellaPrint(output, context);
    } else {
        printf("The function %s is suppos to be compiler defined but it is not defined in builtInFunctions.\n", nameFunc);
        context->errors++;
        return;
    }   
}