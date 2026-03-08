#include "../include/assemblyInstr/helperFuncAS.h"

void setStackLayout(Operand op, StackLayout *stack){
    if(op.IR_type == 0){
        return;
    }

    if(op.IR_type == IR_CONST){
        return;
    } 
    else if (op.IR_type == IR_VAR) {
        setVarStack(op, stack);
        return;
    } 
    else {
        setTmpStack(op,stack);
        return;
    }
}
