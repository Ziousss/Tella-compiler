#include "../include/assemblyInstr/assemblyInstrHeader.h"

void assignAS(IRstruct *assign, FILE *output, StackLayout *stack){
    Operand src = assign->data.assign.src;
    Operand dst = assign->data.assign.dst;

    if(src.IR_type == IR_CONST){
        movConstant(src, output, "rax");
    } else {
        int srcOffset = getOffset(src, stack);
        fprintf(output, "mov rax, [rbp %+d]\n", srcOffset);
    }
    
    int dstOffset = getOffset(dst, stack);
    fprintf(output, "mov [rbp %+d], rax\n", dstOffset);
}