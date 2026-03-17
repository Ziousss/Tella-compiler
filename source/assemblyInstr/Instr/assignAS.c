#include "../include/assemblyInstr/assemblyInstrHeader.h"

void assignAS(IRstruct *assign, FILE *output, StackLayout *stack){
    Operand src = assign->data.assign.src;
    Operand dst = assign->data.assign.dst;

    if(src.IR_type == IR_CONST){
        CstTypes cstType = src.data.IR_constant.cst_type;
        switch (cstType) {
        case IR_CHAR:
            fprintf(output, "mov rax, %c\n", src.data.IR_constant.value.chr);
            break;
        
        case IR_STRING:
            printf("String not implemented for assignment yet.\n");
            break;

        case IR_INT:
            fprintf(output, "mov rax, %d\n", src.data.IR_constant.value.number);
            break;

        case IR_BOOL:
            fprintf(output, "mov rax, %d\n", src.data.IR_constant.value.boolean);
            break;
        
        default:
            printf("Unknown constant in assignAS.\n");
            break;
        }
    } else {
        int srcOffset = getOffset(src, stack);
        fprintf(output, "mov rax, [rbp %+d]\n", srcOffset);
    }
    
    int dstOffset = getOffset(dst, stack);
    fprintf(output, "mov [rbp %+d], rax\n", dstOffset);
}