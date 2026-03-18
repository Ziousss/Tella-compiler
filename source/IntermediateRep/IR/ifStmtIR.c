#include "../include/IntermediateRep/IRheader.h"

//Will finish later wanna tart the machine code
//Some warnings say unused variables here but I did not finish it and this is never called so it is normal
void ifStmtIR(ASTnode *ifStmt, IRContext *context){
    ASTnode *condition = ifStmt->data.if_node.condition;
    ASTnode *ifNode = ifStmt->data.if_node.if_branch;
    ASTnode *elseNode = ifStmt->data.if_node.else_branch;
    int error = context->errors;

    int condLabel = context->current_label++;
    int elseLabel = context->current_label++;
    int endlabel = context->current_label++;
    IRstruct *labelIR = newLabel(context, condLabel);
    emit(labelIR, context);

    Operand conditionOP = expressionIR(condition, context);
    if(context->errors != error){
        return;
    }

    IRstruct *conditionIR = newJmpFalse(context, elseLabel, conditionOP);
    emit(conditionIR, context);

    blockIR(ifNode, context);

    IRstruct *jmpEnd = newJmp(context, endlabel);
    emit(jmpEnd, context);

    IRstruct *elseLabelIR = newLabel(context, elseLabel);
    emit(elseLabelIR, context);

    context->returned = false; 

    if(elseNode != NULL){
        blockIR(elseNode,context);
    }

    IRstruct *end = newLabel(context, endlabel);
    emit(end, context);
}