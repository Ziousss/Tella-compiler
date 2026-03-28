#include "../include/assemblyInstr/assemblyInstrHeader.h"

void condJumpAS(IRstruct *condJump, FILE *output, StackLayout *stack, ASContext *context){
    Operand condition = condJump->data.condition_jump.condition;
    int target = condJump->data.condition_jump.target_label;

    if(condition.IR_type != IR_CONST){
        int offset = getOffset(condition, stack, context);
        fprintf(output, "mov rax, [rbp %+d]\n", offset);
    } else {
        switch (condition.data.IR_constant.cst_type){
        case IR_BOOL:
            fprintf(output, "mov rax, %d\n", condition.data.IR_constant.value.boolean);
            break;
        
        default:
            printf("CstType is not boolean for a constant in a conditional jump.\n");
            break;
        }
    }
    
    fprintf(output, "test rax, rax\n");
    fprintf(output, "je L%d\n", target);
}