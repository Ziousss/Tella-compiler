#include "../include/semanticAnalyser/nodeAnalyser.h"

void funcSignAnalyser(ASTnode *funcSign, SemContext *context){
    if(find_in_scope(funcSign->data.func_def.name, context)){
        printf("Redefinition of the function signature %s.\n", funcSign->data.func_def.name);
        context->error_count++;
        return;
    }
    if(funcSign->data.func_def.body != NULL){
        printf("Internal error: %s signature has body none NULL.\n", funcSign->data.func_def.name);
        context->error_count++;
        return;
    }

    SymbolNode *sym = malloc(sizeof(SymbolNode));
    if(sym == NULL){
        printf("Malloc failed for sym AST_FUNC_SIGN.\n");
        context->error_count++;
        return;
    }

    sym->kind = SEM_SIGN;
    sym->name = funcSign->data.func_def.name;
    sym->isArr = false;
    sym->line = funcSign->line;
    sym->next = NULL;
    sym->type = fromTokToSem(funcSign->data.func_def.return_type);
    
    SymbolParams *symParam = getParams(funcSign->data.func_def.parameters);    
    sym->param = symParam;

    int paramCount = 0;
    SymbolParams *tmp = symParam;
    while(tmp != NULL){
        paramCount++;
        tmp = tmp->next;
    }

    sym->param_count = paramCount;

    push_variables(sym, context);
    return;    
}