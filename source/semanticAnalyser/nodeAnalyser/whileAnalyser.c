#include "../include/semanticAnalyser/nodeAnalyser.h"

void whileAnalyser(ASTnode *whileAst, SemContext *context){
    SemanticType condition = expressionAnalyser(whileAst->data.while_node.condition, context);
    if(condition != SEM_BOOL){
        printf("In the while loop line %d, the condition has to be of type bool.\n", whileAst->line);
        context->error_count++;
        return;
    }

    blockAnalyser(whileAst->data.while_node.block,context, true);
    return;
}