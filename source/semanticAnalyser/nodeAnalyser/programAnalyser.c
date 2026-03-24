#include "../include/semanticAnalyser/nodeAnalyser.h"

GlobalFunc *programAnalyser(ASTnode *program) {
    if(program == NULL || program->ast_type != AST_PROGRAM){
        printf("This is not a program ast, check the given ast.\n");
        return NULL;
    }

    SemContext *context = malloc(sizeof(SemContext));
    if(context == NULL){
        printf("Malloc error for context in programAnalyser.\n");
        return NULL;
    }
    context->current_function = NULL;
    context->error_count = 0;
    context->current_scope = NULL;
    context->saw_return = false;
    context->IRsym = NULL;

    push_scope(context);
    ASTnode *func_def_node = program->data.program_node.func_def;
    while (func_def_node != NULL)
    {
        funcDefAnalyser(func_def_node, context);
        func_def_node = func_def_node->next;
    } 

    GlobalFunc *functionsList = getAllFunctions(context);
    if(context->error_count != 0){
        return NULL;
    }

    GlobalFunc *current = functionsList;
    while (current != NULL)
    {
        current->sym = context->IRsym;
        current = current->next;
    }
    
    return functionsList;
}