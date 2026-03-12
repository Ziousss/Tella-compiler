#include "../include/IntermediateRep/IRheader.h"

void forIR(ASTnode *forStmt, IRContext *context){
    // initialisation — either VAR_DECL or ASSIGN_EXPR
    ASTnode *init = forStmt->data.for_node.initialisation;
    if(init->ast_type == AST_VAR_DECL){
        if(init->data.declaration.expression != NULL){
            Operand dst;
            dst.IR_type = IR_VAR;
            dst.data.IR_Variable.identifier = init->data.declaration.identifier;
            Operand src = expressionIR(init->data.declaration.expression, context);
            IRstruct *declaration = newAssign(context, dst, src);
            emit(declaration, context);
        }
    } else if(init->ast_type == AST_ASSIGN_EXPR){
        Operand dst;
        dst.IR_type = IR_VAR;
        dst.data.IR_Variable.identifier = init->data.assign.target;
        Operand src = expressionIR(init->data.assign.value, context);
        IRstruct *assign = newAssign(context, dst, src);
        emit(assign, context);
    }

    // condition
    int condition_label = context->current_label++;
    int end_label = context->current_label++;
    IRstruct *label = newLabel(context, condition_label);
    emit(label, context);
    Operand condition = expressionIR(forStmt->data.for_node.condition, context);
    IRstruct *condIR = newJmpFalse(context, end_label, condition);
    emit(condIR, context);

    // body
    blockIR(forStmt->data.for_node.block, context);

    // incrementation — always AST_ASSIGN_EXPR from loopAssignParse
    ASTnode *inc = forStmt->data.for_node.incrementation;
    Operand inc_dst;
    inc_dst.IR_type = IR_VAR;
    inc_dst.data.IR_Variable.identifier = inc->data.assign.target;
    Operand inc_src = expressionIR(inc->data.assign.value, context);
    IRstruct *incIR = newAssign(context, inc_dst, inc_src);
    emit(incIR, context);

    // jump back and end label
    IRstruct *jumpBack = newJmp(context, condition_label);
    IRstruct *forEnd = newLabel(context, end_label);
    emit(jumpBack, context);
    emit(forEnd, context);
}