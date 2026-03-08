#include "../include/IntermediateRep/IRheader.h"

void returnIR(ASTnode *returnNode, IRContext *context){
    IRstruct *retIR;
    if(returnNode->data.return_node.expr == NULL){
        retIR = newReturn(context, (Operand){.ret_void = true});
        emit(retIR, context);
        return;
    }
    Operand retExpr = expressionIR(returnNode->data.return_node.expr, context);
    retIR = newReturn(context, retExpr);
    emit(retIR, context);
}