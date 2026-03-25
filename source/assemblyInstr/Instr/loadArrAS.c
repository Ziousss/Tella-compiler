#include "../include/assemblyInstr/assemblyInstrHeader.h"

void loadArrAS(IRstruct *loadArr, FILE *output, StackLayout *stack, ASContext *context){
    Operand base = loadArr->data.loadArray.base;
    Operand index = loadArr->data.loadArray.index;
    Operand dst = loadArr->data.loadArray.dst;

    int dstOffset = getOffset(dst, stack,context);
    int baseOffset = getOffset(base, stack, context);
    int indexOffset = 0;
    if(index.IR_type != IR_CONST){
        indexOffset = getOffset(index, stack, context); 
    }

    //index in rax
    if(indexOffset == 0){
        if(index.data.IR_constant.cst_type == IR_INT){
            fprintf(output, "mov rax, %d\n", index.data.IR_constant.value.number);
        } else {
            printf("CstType is not an INT in loadArrAS.\n");
            context->errors++;
            return;
        }
    } else {
        fprintf(output, "mov rax, [rbp %+d]\n", indexOffset);
    }

    fprintf(output, "imul rax, %d\n", base.data.IR_Variable.elementSize);
    fprintf(output, "lea rcx, [rbp %+d]\n", baseOffset);
    fprintf(output, "sub rcx, rax\n");
    //Now the array is loaded in rcx

    fprintf(output, "mov rbx, [rcx]\n");
    fprintf(output, "mov [rbp %+d], rbx\n", dstOffset);

    return;
}