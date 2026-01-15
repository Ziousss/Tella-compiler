#include "../include/semanticAnalyser/nodeAnalyser.h"

void funcDefAnalyser(ASTnode *funcDefAst, SemContext *context){
    if(funcDefAst == NULL){
        return;
    }

    SymbolNode *funcDefSem = malloc(sizeof(SymbolNode));
    SemanticType type = fromTokToSem(funcDefAst->data.func_def.return_type);
    if(type == SEM_ERROR){
        printf("the return type of the function %s is not supported yet.\n", funcDefAst->data.func_def.name);
        context->error_count += 1;
        return;
    }
    funcDefSem->name = strdup(funcDefAst->data.func_def.name);
    funcDefSem->kind = SEM_FCT;
    funcDefSem->type = type;
    funcDefSem->next = NULL;

    push_to_scope(funcDefSem);
    context->current_function = funcDefSem;

    int count = 0;
    ParameterNode *paramAst = funcDefAst->data.func_def.parameters;
    while(paramAst){
        SymbolNode *paramSem = malloc(sizeof(SymbolNode));

        paramSem->kind = SEM_PARAM;
        paramSem->name = strdup(paramAst->name);
        paramSem->type = fromTokToSem(paramAst->ret_type);
        paramSem->next = NULL;

        push_to_scope(paramSem);
        paramAst = paramAst->next;
    }

    blockAnalyser(funcDefAst->data.func_def.body, context);
    
    context->current_function = NULL;
    pop_out_scope(count);
}