#include "../include/IntermediateRep/IRheader.h"

void funcDefIR(ASTnode *funcdef, IRContext *context){
    if(funcdef->ast_type != AST_FUNC_DEF && funcdef->ast_type != AST_FUNC_DEF_MAIN){
        printf("The wrong ASTnode has been given to the function funcDefIR.\n");
        return;
    }

    context->returned = false;
    IRstruct *IRFuncDef = newFunc(context, funcdef->data.func_def.name);
    if(IRFuncDef == NULL){
        printf("newFunc failed in funcDefIR.\n");
        return;
    }

    emit(IRFuncDef, context);
    if(funcdef->data.func_def.param){
        ParameterNode *paramTree = funcdef->data.func_def.parameters;
        ParameterNode *tmp = paramTree;

        int param = 0;
        while(tmp != NULL){
            param++;
            tmp = tmp->next;
        }

        if(paramTree != NULL && param != paramTree->count){
            printf("Something off with the parameters of the function %s.\n", funcdef->data.func_def.name);
            printf("Number of parameters real vs expected = %d/%d\n", param, paramTree->count);
            context->errors++;
            return;
        }

        tmp = paramTree;
        int param_index = 0;
        while(tmp != NULL){
            IRstruct *param = newParam(context, param_index, tmp->name, fromTokToCstType(tmp->ret_type));
            if(param == NULL){
                printf("New param failed.\n");
                return;
            }
            
            emit(param, context);
            param_index++;
            tmp = tmp->next;
        }
    }

    blockIR(funcdef->data.func_def.body, context);
}