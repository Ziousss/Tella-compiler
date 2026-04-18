#include "../include/semanticAnalyser/nodeAnalyser.h"

SemanticType funcCallAnalyser(ASTnode *funcCallAst, SemContext *context){
    char *name = funcCallAst->data.func_call.name;
    SymbolNode *funcCallNode = find_in_scope(name,context);
    if(funcCallNode == NULL || (funcCallNode->kind != SEM_FCT && funcCallNode->kind != SEM_SIGN)){
        printf("You call the function %s but it has not been defined yet.\n", name);
        context->error_count++;
        return SEM_ERROR;
    }

    int paramCallCount = 0;
    ArgNode *cur = funcCallAst->data.func_call.args;
    while(cur){
        paramCallCount++;
        cur = cur->next;
    }

    if(paramCallCount != funcCallNode->param_count){
        printf("Number of arguments different from function definition %s and function call line %ld file %s, expected %d but found %d.\n", funcCallNode->name, funcCallAst->line, funcCallAst->fileName, funcCallNode->param_count, paramCallCount);
        context->error_count++;
        return SEM_ERROR;
    }

    ArgNode *arg = funcCallAst->data.func_call.args;
    SymbolParams *paramSym = funcCallNode->param;
    SymbolParams* tmp = paramSym;

    for(int i = 0; i < paramCallCount; i++){
        SemanticType param_type = expressionAnalyser(arg->expression, context);

        if(param_type == SEM_ERROR){
            return SEM_ERROR;
        }
        if(param_type != tmp->type){
            printf("Type mismatch in call to '%s' at line %ld file %s: argument %d is %s but expected %s (%d).\n",funcCallNode->name,  funcCallAst->line, funcCallAst->fileName,  i + 1,   fromSemToString(param_type), fromSemToString(tmp->type), tmp->type);
            context->error_count++;
            return SEM_ERROR;
        }
        arg = arg->next;
        tmp = tmp->next;
    }
    while(paramSym != NULL){
        SymbolParams *next = paramSym->next;
        free(paramSym->name);
        free(paramSym);
        paramSym = next;
    }
    
    return funcCallNode->type;
}