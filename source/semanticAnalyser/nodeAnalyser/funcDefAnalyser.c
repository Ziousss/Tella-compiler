#include "../include/semanticAnalyser/nodeAnalyser.h"

void funcDefAnalyser(ASTnode *funcDefAst, SemContext *context){
    if(funcDefAst == NULL){
        return;
    }
    bool funcNull = false;
    SymbolNode *func = find_in_scope(funcDefAst->data.func_def.name, context);
    if(func != NULL && func->kind != SEM_SIGN){
        printf("Function redefinition. The function called %s is already defined wih that name.\n", funcDefAst->data.func_def.name);
        context->error_count++;
        return;
    } else if (func == NULL){
        funcNull = true;
    }

    //Is tere a func signature for this function
    bool sign = false;
    if(func != NULL){
        sign = true;
        if(strcmp(func->name, funcDefAst->data.func_def.name) != 0) {
            printf("Internal error: given name of the signature of the function %s is not the same as the function itself (%s).\n", func->name, funcDefAst->data.func_def.name);
            context->error_count++;
            return;
        }

        if(func->type != fromTokToSem(funcDefAst->data.func_def.return_type)){
            printf("Signature type of the function %s is not the same as the actual return type defined.\n", func->name);
            context->error_count++;
            return;
        }
    }

    SymbolNode *funcDefSem = malloc(sizeof(SymbolNode));
    if(funcDefSem == NULL){
        printf("Malloc failed for funcDefSem\n");
        context->error_count++;
        return;
    }
    
    SemanticType type = fromTokToSem(funcDefAst->data.func_def.return_type);
    if(type == SEM_ERROR){
        printf("The return type of the function %s is not supported yet.\n", funcDefAst->data.func_def.name);
        context->error_count++;
        return;
    }

    funcDefSem->name = strdup(funcDefAst->data.func_def.name);
    funcDefSem->kind = SEM_FCT;
    funcDefSem->type = type;
    funcDefSem->next = NULL;
    funcDefSem->size = NULL;

    //This is useful for function calls
    int paramCount = 0;
    if(funcDefAst->data.func_def.parameters != NULL){
        int param = funcDefAst->data.func_def.parameters->count;
        paramCount = param;
    }
    funcDefSem->param_count = paramCount;

    ParameterNode *param = funcDefAst->data.func_def.parameters;
    SymbolParams *symParams = getParams(param);

    if(sign){
        SymbolParams *funcSignParams = NULL;
        if(!funcNull && func->param != NULL){
            funcSignParams = func->param;
        }

        if(symParams == NULL && funcSignParams != NULL){
            printf("Function definition %s has no parameters but the function signature does.\n", func->name);
            context->error_count++;
            return;
        } else if (symParams != NULL && funcSignParams == NULL){
            printf("Function signature %s has no parameters but the function definition does.\n", funcDefAst->data.func_def.name);
            context->error_count++;
            return;
        }
    }

    if(sign && symParams != NULL){
        SymbolParams *tmp = symParams;
        
        while (tmp->next != NULL){
            tmp = tmp->next;
        }
        int argCount = tmp->count;
        
        tmp = symParams;
        SymbolParams *argSign = func->param;
        SymbolParams *tmpSign = argSign;

        for(int i = 0; i < argCount; i++){
            if(strcmp(tmp->name, tmpSign->name) != 0){
                printf("Argument number %d in the function def %s does not have the same name as the one used in its signature.\n", i+1, tmp->name);
                context->error_count++;
            }

            if(tmp->type != tmpSign->type){
                printf("Argument number %d in the function def %s does not have the same type as the one used in its signature.\n", i+1, tmp->name);
                context->error_count++;
            }
        }

        tmp = symParams;
        while(tmp != NULL){
            SymbolParams *next = tmp->next;
            free(tmp);
            tmp = next;
        }
    }

    //pushed to global scope
    push_variables(funcDefSem, context);

    //creates function scope
    push_scope(context);

    context->current_function = funcDefSem;
    context->saw_return = false;

    //Push parameters to the scope
    ParameterNode *paramAst = funcDefAst->data.func_def.parameters;

    for(int i = 0; i < paramCount; i++){
        SymbolNode *paramSem = malloc(sizeof(SymbolNode));
        if(paramSem == NULL){
            printf("malloc for Paramsem failed.\n");
            context->error_count++;
            return;
        }

        paramSem->kind = SEM_PARAM;
        paramSem->name = strdup(paramAst->name);
        paramSem->type = fromTokToSem(paramAst->ret_type);
        paramSem->size = NULL;
        paramSem->next = NULL;

        push_variables(paramSem, context);

        
        IRsymbole *symIR = newIRsym(strdup(paramAst->name), fromTokToSem(paramAst->ret_type), -1, NULL, SEM_PARAM);
        pushIRSym(symIR,context);

        paramAst = paramAst->next;
    }

    blockAnalyser(funcDefAst->data.func_def.body, context, false);
    
    if(context->current_function->type != SEM_VOID && !(context->saw_return)){
        printf("The function %s has a return type %s but no return has been found in it.\n", context->current_function->name, fromSemToString(context->current_function->type));
        context->error_count++;
        return;
    }

    context->current_function = NULL;
    
    while(symParams != NULL){
        SymbolParams *next = symParams->next;
        free(symParams->name);
        free(symParams);
        symParams = next;
    }
    
    pop_scope(context);
}