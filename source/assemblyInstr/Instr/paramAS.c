#include "../include/assemblyInstr/assemblyInstrHeader.h"

char const *paramReg[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};

void paramAS(IRstruct *parameter, FILE *output, StackLayout *stack){
    const char *reg = paramReg[parameter->data.parameters.parameter.data.IR_Variable.param_index];
    Operand param = parameter->data.parameters.parameter;
    int offset = getOffset(param, stack);
    fprintf(output, "mov [rbp %+d], %s\n", offset, reg);
}