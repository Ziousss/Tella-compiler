#include "../include/IntermediateRep/IRheader.h"

void funcDefIR(ASTnode *funcdef, IRContext *context){
    if(funcdef->ast_type != AST_FUNC_DEF && funcdef->ast_type != AST_FUNC_DEF_MAIN){
        printf("The wrong ASTnode has been given to the function funcDefIR.\n");
        return;
    }

    //Forgot to handle parameters
    ParameterNode *paramTree = funcdef->data.func_def.parameters;
    ParameterNode *tmp = paramTree;

    int param = 0;
    while(tmp != NULL){
        param++;
        tmp = tmp->next;
    }


    if(paramTree != NULL && param != paramTree->count){
        printf("Something off with the parameters IR in function def IR.\n");
        context->errors++;
        return;
    }

    context->returned = false;
    IRstruct *IRFuncDef = newFunc(context, funcdef->data.func_def.name);
    if(IRFuncDef != NULL){
        emit(IRFuncDef, context);
    }

    tmp = paramTree;
    int param_index = 0;
    tmp->ret_type;
    while(tmp != NULL){
        IRstruct *param = newParam(context, param_index, tmp->name, fromTokToCstType(tmp->ret_type));
        if(param == NULL){
            return;
        }

        emit(param, context);
        param_index++;
        tmp = tmp->next;
    }

    blockIR(funcdef->data.func_def.body, context);
}