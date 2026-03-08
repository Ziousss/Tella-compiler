#include "../include/assemblyInstr/assemblyInstrHeader.h"

void binaryAS(IRstruct *binary, FILE *output){
    Operand dst = binary->data.binary.dst;
    Operand src1 = binary->data.binary.src1;
    Operand src2 = binary->data.binary.src2;

    IRoperation op = binary->op;

    switch (op) {
        case IR_ADD:
        case IR_SUB:
        case IR_MULT:
        case IR_DIV:
        case IR_EQEQ:
        case IR_UNEQ:
        case IR_GR:
        case IR_GREQ:
        case IR_LESS:
        case IR_LESSEQ:
    }
}