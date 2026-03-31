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

    if(loadArr->data.loadArray.isPointer == true){
        fprintf(output, "mov rcx, [rbp %+d]\n", baseOffset);
        fprintf(output, "add rcx, rax\n");
    } else {
        printf("HERE\n");
        fprintf(output, "lea rcx, [rbp %+d]\n", baseOffset);
        fprintf(output, "sub rcx, rax\n");
    }

    //Now the array is loaded in rcx
    int size = base.data.IR_Variable.elementSize;
    if(size == 1){
        fprintf(output, "movzx rbx, byte ptr [rcx]\n");
    }
    else if(size == 4){
        fprintf(output, "mov ebx, dword ptr [rcx]\n");
    }
    else if(size == 8){
        fprintf(output, "mov rbx, qword ptr [rcx]\n");
    }
    else{
        printf("Unsupported element size %d in loadArrAS\n", size);
        context->errors++;
        return;
    }

    fprintf(output, "mov [rbp %+d], rbx\n", dstOffset);

    return;
}