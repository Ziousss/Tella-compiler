#include "../include/semanticAnalyser/nodeAnalyser.h"

void blockAnalyser(ASTnode *blockAst, SemContext *context, bool new_scope){
    if(blockAst == NULL){
        return;
    }
    ASTnode *stmt = blockAst->data.block.stmts;
    bool pushed = false;

    if(new_scope){
        pushed = true;
        push_scope(context);
    }

    while(stmt){
        stmtAnalyser(stmt, context);
        stmt = stmt->next;
    }
    if(pushed){
        pop_scope(context);
    }
}