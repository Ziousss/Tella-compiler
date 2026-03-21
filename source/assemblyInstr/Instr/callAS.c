#include "../include/assemblyInstr/assemblyInstrHeader.h"

void callAS(IRstruct *call, FILE *output, StackLayout *stack, ASContext *context){
    Operand dst = call->data.call.dst;

    fprintf(output, "call %s\n", call->data.call.func_name);
    if(dst.IR_type != IR_VOID_OPERAND){
        int offset = getOffset(dst, stack, context);
        
        //does - for variables etc and + for parameters
        fprintf(output, "mov [rbp %+d], rax\n", offset);
    }

    stack->arg_count = 0;
}