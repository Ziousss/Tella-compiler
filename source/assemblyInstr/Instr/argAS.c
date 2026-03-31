#include "../include/assemblyInstr/assemblyInstrHeader.h"

char const *param_reg[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};

void argAS(IRstruct *arg, FILE *output, StackLayout *stack, ASContext* context){
    //will add stack argument later.
    if(stack->arg_count >= 6){
        printf("ERROR: Too many arguments (> 6)\n");
        context->errors++;
        return;
    }

    Operand argOp = arg->data.arg.value;
    IRtype argType = argOp.IR_type;
    int indexContext = stack->arg_count;
    const char *reg = param_reg[stack->arg_count++];

    switch (argType){
        case IR_VAR:{
            int varOffset = findVarInStack(argOp, stack);
            fprintf(output, "mov %s, [rbp %+d]\n", reg, varOffset);
            context->offset[indexContext] = varOffset;
            context->argType[indexContext] = IR_VAR;

            IRstruct *rodata = getRodataString(context, -1, argOp.data.IR_Variable.string);
            if(rodata == NULL){
                printf("Rodata null in argAS\n");
                context->errors++;
                return;
            }

            context->stringID[indexContext] = rodata->data.rodata.stringID;
            break;
        }
        
        case IR_TMP:{
            int tmpOffset = stack->tmp[argOp.data.IR_tmp.id_tmp];
            fprintf(output, "mov %s, [rbp %+d]\n", reg, tmpOffset);
            context->offset[indexContext] = tmpOffset;
            context->argType[indexContext] = IR_TMP;
            break;
        }

        case IR_CONST:{
            CstTypes cstType = argOp.data.IR_constant.cst_type;
            context->offset[indexContext] = 1;
            context->argType[indexContext] = IR_CONST;
            switch (cstType) {
            case IR_STRING: {
                int stringID = argOp.data.IR_constant.value.stringID;
                fprintf(output, "lea %s, [rip + string_%d]\n", reg, stringID);
                context->stringID[indexContext] = stringID;
                break;
            }
            
            case IR_INT:{
                fprintf(output, "mov %s, %d\n", reg, argOp.data.IR_constant.value.number);
                break;
            }

            case IR_CHAR:{
                fprintf(output, "mov %s, %d\n", reg, argOp.data.IR_constant.value.chr);
                break;
            }

            case IR_BOOL:{
                fprintf(output, "mov %s, %d\n", reg, argOp.data.IR_constant.value.boolean);
                break;
            }

            default:{
                printf("Cst with unknown type in argAS.\n");
                context->errors++;
                break;
            }
            }  
            break;  
        }

    default:
        printf("Arg type not known in argAS.\n");
        context->errors++;
        break;
    }
}