#include "../include/IntermediateRep/IRheader.h"

//Will finish later wanna tart the machine code
//Some warnings say unused variables here but I did not finish it and this is never called so it is normal
void ifStmtIR(ASTnode *ifStmt, IRContext *context){
    ASTnode *condition = ifStmt->data.if_node.condition;
    ASTnode *ifNode = ifStmt->data.if_node.if_branch;
    ASTnode *elseNode = ifStmt->data.if_node.else_branch;

    int error = context->errors;
    Operand conditionOP = expressionIR(condition, context);
    if(context->errors != error){
        return;
    }
}