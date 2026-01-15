#include "../include/semanticAnalyser/nodeAnalyser.h"

void blockAnalyser(ASTnode *blockAst, SemContext *context){
    ASTnode *stmt = blockAst->data.block.stmts;
    int count = 0;

    while(stmt){
        stmtAnalyser(stmt, &count, context);
        stmt = stmt->next;
    }

    pop_out_scope(count);
}