#include "../include/semanticAnalyser/nodeAnalyser.h"

SemanticType funcCallAnalyser(ASTnode *funcCallAst, SemContext *context){
    char *name = funcCallAst->data.func_call.name;
    SymbolNode *funcCallNode = find_in_scope(name, context);
    if(funcCallNode == NULL || funcCallNode->kind != SEM_FCT){
        printf("You call the function %s but it has not been defined yet.\n", name);
        context->error_count++;
        return SEM_ERROR;
    }

    int param_call_count = 0;
    ArgNode *cur = funcCallAst->data.func_call.args;
    while(cur){
        param_call_count++;
        cur = cur->next;
    }

    if(param_call_count != funcCallNode->param_count){
        printf("Number of arguments different from function definition %s and function call line %d.\n", funcCallNode->name, funcCallAst->line);
        context->error_count++;
        return SEM_ERROR;
    }

    ArgNode *arg = funcCallAst->data.func_call.args;

    for(int i = 0; i < param_call_count; i++){
        SemanticType type = expressionAnalyser(arg->expression, context);

        if(type == SEM_ERROR){
            return SEM_ERROR;
        }
        if(type != funcCallNode->param[i]){
            printf("Type mismatch in call to '%s' at line %d: argument %d is %s but expected %s.\n",funcCallNode->name,  funcCallAst->line,  i + 1,   fromSemToString(type), fromSemToString(funcCallNode->param[i]));
            context->error_count++;
            return SEM_ERROR;
        }
        arg = arg->next;
    }
    return funcCallNode->type;
}