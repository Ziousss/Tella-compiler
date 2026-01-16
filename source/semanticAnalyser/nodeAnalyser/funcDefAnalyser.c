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

    //This is useful for function calls
    int param_count = funcDefAst->data.func_def.parameters->count;
    funcDefSem->param_count = param_count;
    funcDefSem->param = malloc(sizeof(SemanticType) * param_count);

    ParameterNode *param = funcDefAst->data.func_def.parameters;
    int i = 0;
    while(param){
        funcDefSem->param[i++] = param->ret_type;
        param = param->next;
    }
    
    push_scope(context);
    push_variables(funcDefSem, context);

    context->current_function = funcDefSem;

    ParameterNode *paramAst = funcDefAst->data.func_def.parameters;
    while(paramAst){
        SymbolNode *paramSem = malloc(sizeof(SymbolNode));

        paramSem->kind = SEM_PARAM;
        paramSem->name = strdup(paramAst->name);
        paramSem->type = fromTokToSem(paramAst->ret_type);
        paramSem->next = NULL;

        push_variables(paramSem, context);
        paramAst = paramAst->next;
    }

    blockAnalyser(funcDefAst->data.func_def.body, context, false);
    
    if(context->current_function->type != SEM_VOID){
        if(!(context->saw_return)){
            printf("The function %s has a return type %s but no return has been found in it.\n", context->current_function->name, fromSemToString(context->current_function->type));
            context->error_count++;
            return;
        }
    }

    context->current_function = NULL;
    pop_scope(context);
}