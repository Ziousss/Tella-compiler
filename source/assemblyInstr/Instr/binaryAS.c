#include "../include/assemblyInstr/assemblyInstrHeader.h"

void binaryAS(IRstruct *binary, FILE *output, StackLayout *stack){
    Operand dst = binary->data.binary.dst;
    Operand src1 = binary->data.binary.src1;
    Operand src2 = binary->data.binary.src2;

    //Puts the values/tmp/variables in rax and rbx
    if(src1.IR_type == IR_CONST){
        movConstant(src1, output, "rax");
    } else {
        int src1Offset = getOffset(src1, stack);
        fprintf(output, "mov rax, [rbp %+d]\n", src1Offset);
    }
    fprintf(output, "push rax\n");

    if(src2.IR_type == IR_CONST){
        movConstant(src2, output, "rax");
    } else {
        int src2Offset = getOffset(src2, stack);
        fprintf(output, "mov rax, [rbp %+d]\n", src2Offset);
    }
    fprintf(output, "pop rbx\n");

    //src 1 = rbx and src2 = rax

    IRoperation op = binary->op;
    switch (op) {
        case IR_ADD: {
            fprintf(output, "add rax, rbx\n");
            break;
        }

        case IR_SUB:{
            fprintf(output, "sub rbx, rax\n");
            fprintf(output, "mov rax, rbx\n");
            break;
        }

        case IR_MULT:{
            fprintf(output, "imul rax, rbx\n");
            break;
        }

        case IR_DIV:{
            fprintf(output, "mov r10, rax\n");
            fprintf(output, "mov rax, rbx\n");
            fprintf(output, "cqo\n");
            fprintf(output, "idiv r10\n");
            break;
        }

        case IR_EQEQ:{
            fprintf(output, "cmp rbx, rax\n");
            fprintf(output, "sete al\n");
            fprintf(output, "movzx eax, al\n");
            break;
        }

        case IR_UNEQ:{
            fprintf(output, "cmp rbx, rax\n");
            fprintf(output, "setne al\n");
            fprintf(output, "movzx eax, al\n");
            break;
        }

        case IR_GR:{
            fprintf(output, "cmp rbx, rax\n");
            fprintf(output, "setg al\n");
            fprintf(output, "movzx eax, al\n");
            break;
        }

        case IR_GREQ:{
            fprintf(output, "cmp rbx, rax\n");
            fprintf(output, "setge al\n");
            fprintf(output, "movzx eax, al\n");
            break;
        }

        case IR_LESS:{
            fprintf(output, "cmp rbx, rax\n");
            fprintf(output, "setl al\n");
            fprintf(output, "movzx eax, al\n");
            break;
        }

        case IR_LESSEQ:{
            fprintf(output, "cmp rbx, rax\n");
            fprintf(output, "setle al\n");
            fprintf(output, "movzx eax, al\n");
            break;
        }

        default:{
            printf("Unknown binary operation in binaryAS.\n");
            return;
        }
    }

    int dstOffset = getOffset(dst, stack);
    if(dstOffset == 0){
        printf("Dst not found for binary operation in binaryAS.\n");
        return;
    }
    fprintf(output, "mov [rbp %+d], rax\n", dstOffset);

    return;
}