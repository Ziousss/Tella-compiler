#include "../include/IntermediateRep/IRheader.h"

IRstruct *programIR(ASTnode *program, GlobalFunc *definedFunc){
    if(program->ast_type != AST_PROGRAM){
        printf("Given AST is not the program AST.\n");
        return NULL;
    }

    IRContext *context = malloc(sizeof(IRContext));
    if(context == NULL){
        printf("Malloc error in programIR.\n");
        return NULL;
    }

    context->head = NULL;
    context->tail = NULL;
    context->current_label = 0;
    context->current_tmp = 0;
    context->errors = 0;

    initGlobalFunctions(definedFunc);
    ASTnode *funcdef = program->data.program_node.func_def;
    while(funcdef != NULL){
        funcDefIR(funcdef, context);
        funcdef = funcdef->next;
    }

    if(context->errors == 0){
        return context->head;
    }

    printf("Failed somewhere, %d errors.\n", context->errors);
    return NULL;

}