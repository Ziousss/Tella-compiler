#include "../include/assemblyInstr/assemblyInstrHeader.h"

void assignAS(IRstruct *assign, FILE *output, StackLayout *stack, ASContext *context){
    Operand src = assign->data.assign.src;
    Operand dst = assign->data.assign.dst;

    if(src.IR_type == IR_CONST){
        movConstant(src, output, "rax", context);
    } else {
        int srcOffset = getOffset(src, stack, context);
        fprintf(output, "mov rax, [rbp %+d]\n", srcOffset);
    }
    
    int dstOffset = getOffset(dst, stack, context);
    fprintf(output, "mov [rbp %+d], rax\n", dstOffset);
}