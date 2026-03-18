#include "../include/assemblyInstr/assemblyInstrHeader.h"

void returnAS(IRstruct *ret, FILE *output, StackLayout *stack){
    Operand dst = ret->data.ret.return_value;
    IRtype dstType = dst.IR_type;

    switch (dstType) {
        case IR_VAR:
        case IR_TMP: {
            int offset = getOffset(dst, stack);
            fprintf(output, "mov rax, [rbp %+d]\n", offset);
            break;
        }

        case IR_CONST:{
            movConstant(dst, output, "rax");
            break;
        }

        default:{
            printf("Unknown dstType in returnAS.\n");
            break;
        }
    }

    fprintf(output, "mov rsp, rbp\n");
    fprintf(output, "pop rbp\n");
    fprintf(output, "ret\n");
}