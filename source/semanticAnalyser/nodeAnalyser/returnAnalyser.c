#include "../include/semanticAnalyser/nodeAnalyser.h"

void returnAnalyser(ASTnode *returnAst, SemContext *context){
    if(returnAst == NULL){
        if(context->current_function->type != SEM_VOID){
            printf("Current function does not return type void, but return statement line %d does.\n", returnAst->line);
            context->error_count++;
            return;
        }
        return;
    }

    SemanticType ret_type = expressionAnalyser(returnAst, context);
    SemanticType func_type = context->current_function->type;

    if(ret_type != func_type){
        printf("The function returns %s type but the return statement line %d returns %s type.\n",fromSemToString(func_type), returnAst->line, fromSemToString(ret_type));
        context->error_count++;
        return;
    }
}