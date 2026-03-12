#include "../include/IntermediateRep/IRheader.h"

void funcDefIR(ASTnode *funcdef, IRContext *context){
    if(funcdef->ast_type != AST_FUNC_DEF && funcdef->ast_type != AST_FUNC_DEF_MAIN){
        printf("The wrong ASTnode has been given to the function funcDefIR.\n");
        return;
    }

    //Forgot to handle parameters
    ParameterNode *paramTree = funcdef->data.func_def.parameters;
    int param = 0;
    

    context->returned = false;
    IRstruct *IRFuncDef = newFunc(context, funcdef->data.func_def.name);
    if(IRFuncDef != NULL){
        emit(IRFuncDef, context);
    }

    blockIR(funcdef->data.func_def.body, context);
}