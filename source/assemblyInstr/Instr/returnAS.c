#include "../include/assemblyInstr/assemblyInstrHeader.h"

void returnAS(IRstruct *ret, FILE *output, StackLayout *stack){
    Operand dst = ret->data.ret.return_value;
    IRtype dstType = dst.IR_type;

    switch (dstType) {
    case IR_VAR:
    case IR_TMP:
        int offset = getOffset(dst, stack);
        fprintf(output, "mov rax, [rbp %+d]\n", offset);
        break;

    case IR_CONST:
        CstTypes cstType = dst.data.IR_constant.cst_type;
        switch (cstType) {
        case IR_INT:
            fprintf(output, "mov rax, %d\n", dst.data.IR_constant.value.number);
            break;

        case IR_CHAR:
            fprintf(output, "mov rax, %c\n", dst.data.IR_constant.value.chr);
            break;

        case IR_BOOL:
            fprintf(output, "mov rax, %d\n", dst.data.IR_constant.value.boolean);
            break;

        case IR_STRING:
            printf("Strings not implemented yet in the ASInstr.\n");
            break;
        
        default:
            printf("Unknown CstTyped in returnAS.\n");
            break;
        }    
    default:
        printf("Unknown dstType in returnAS.\n");
        break;
    }

    fprintf(output, "mov rsp, rbp\n");
    fprintf(output, "pop rbp\n");
    fprintf(output, "ret\n");
}