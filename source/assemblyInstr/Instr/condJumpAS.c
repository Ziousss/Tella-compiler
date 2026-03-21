#include "../include/assemblyInstr/assemblyInstrHeader.h"

void condJumpAS(IRstruct *condJump, FILE *output, StackLayout *stack, ASContext *context){
    Operand condition = condJump->data.condition_jump.condition;
    int target = condJump->data.condition_jump.target_label;

    int offset = getOffset(condition, stack, context);
    fprintf(output, "mov rax, [rbp %+d]\n", offset);
    fprintf(output, "test rax, rax\n");
    fprintf(output, "je L%d\n", target);
}