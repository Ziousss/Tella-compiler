#include "../include/IntermediateRep/IRheader.h"

void returnIR(ASTnode *returnNode, IRContext *context){
    IRstruct *retIR;
    if(returnNode->data.return_node.expr == NULL){
        retIR = newReturn(context, (Operand){.IR_type = IR_VOID_OPERAND});
        emit(retIR, context);
        return;
    }
    Operand retExpr = expressionIR(returnNode->data.return_node.expr, context);
    retIR = newReturn(context, retExpr);
    emit(retIR, context);
}