#include "../include/semanticAnalyser/nodeAnalyser.h"

void returnAnalyser(ASTnode *returnAst, SemContext *context){
    ASTnode *returnExpr = returnAst->data.return_node.expr;
    if (context->current_function == NULL) {
        printf("Return statement outside of a function at line %d.\n", returnAst ? returnAst->line : -1);
        context->error_count++;
        return;
    }

    if(returnExpr == NULL){
        if(context->current_function->type != SEM_VOID){
            printf("Current function does not return type void, but return statement line %d does.\n", returnAst->line);
            context->error_count++;
            return;
        }
        return;
    }

    SemanticType ret_type = expressionAnalyser(returnAst->data.return_node.expr, context);
    if(ret_type == SEM_ERROR){
        return;
    }
    SemanticType func_type = context->current_function->type;

    if(ret_type != func_type){
        printf("The function returns %s type but the return statement line %d returns %s type.\n",fromSemToString(func_type), returnAst->line, fromSemToString(ret_type));
        context->error_count++;
        return;
    }

    context->saw_return = true;
    return;
}