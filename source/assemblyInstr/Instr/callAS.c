#include "../include/assemblyInstr/assemblyInstrHeader.h"

void callAS(IRstruct *call, FILE *output, StackLayout *stack){
    Operand dst = call->data.call.dst;

    fprintf(output, "call %s\n", call->data.call.func_name);
    if(dst.IR_type != IR_VOID_OPERAND){
        if(IR_VAR){
            int stackOffset = findVarInStack(dst, stack);
            fprintf(output, "mov [rbp - %d], rax\n", stackOffset);
        } else {
            int tmpOffset = stack->tmp[dst.data.IR_tmp.id_tmp];
            fprintf(output, "mov [rbp - %d], rax\n", tmpOffset);
        }
    }

    stack->arg_count = 0;
}