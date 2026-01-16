#include "../include/semanticAnalyser/nodeAnalyser.h"

void ifAnalyser(ASTnode *ifStmtAst, SemContext *context){
    SemanticType condition_type = expressionAnalyser(ifStmtAst->data.if_node.condition, context);
    if(condition_type == SEM_ERROR){
        return;
    }
    if(condition_type != SEM_INT && condition_type != SEM_BOOL){
        printf("In the if statement line %d, the condition has to be of type boolean or integer, not %s.\n", ifStmtAst->line, fromSemToString(condition_type));
        context->error_count++;
        return;
    }

    blockAnalyser(ifStmtAst->data.if_node.if_branch, context, true);
    if(ifStmtAst->data.if_node.else_branch != NULL){
        blockAnalyser(ifStmtAst->data.if_node.else_branch, context, true);
    }
    return;
}