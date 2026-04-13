#include "../include/semanticAnalyser/nodeAnalyser.h"

SemanticType funcCallAnalyser(ASTnode *funcCallAst, SemContext *context){
    char *name = funcCallAst->data.func_call.name;

    SymbolNode *funcCallNode = find_in_scope(name, context);
    if(funcCallNode == NULL || (funcCallNode->kind != SEM_FCT && funcCallNode->kind != SEM_SIGN)){
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
        printf("Number of arguments different from function definition %s and function call line %ld file %s, expected %d but found %d.\n", funcCallNode->name, funcCallAst->line, funcCallAst->fileName, funcCallNode->param_count, param_call_count);
        context->error_count++;
        return SEM_ERROR;
    }

    ArgNode *arg = funcCallAst->data.func_call.args;
    SymbolParams *paramSym = funcCallNode->param;
    SymbolParams* tmp = paramSym;

    for(int i = 0; i < param_call_count; i++){
        SemanticType param_type = expressionAnalyser(arg->expression, context);

        if(param_type == SEM_ERROR){
            return SEM_ERROR;
        }
        if(param_type != tmp->type){
            printf("Type mismatch in call to '%s' at line %ld file %s: argument %d is %s but expected %s.\n",funcCallNode->name,  funcCallAst->line, funcCallAst->fileName,  i + 1,   fromSemToString(param_type), fromSemToString(tmp->type));
            context->error_count++;
            return SEM_ERROR;
        }
        arg = arg->next;
        tmp = tmp->next;
    }
    return funcCallNode->type;
}