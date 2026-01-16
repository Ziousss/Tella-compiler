#include "../include/semanticAnalyser/nodeAnalyser.h"

bool programAnalyser(ASTnode *program) {
    if(program == NULL || program->ast_type != AST_PROGRAM){
        printf("This is not a program ast, check the given ast.\n");
        return false;
    }

    SemContext *context;
    context->error_count = 0;
    context->current_scope = NULL;

    ASTnode *func_def_node = program->data.program_node.func_def;
    while (func_def_node != NULL)
    {
        funcDefAnalyser(func_def_node, context);
        func_def_node = func_def_node->next;
    } 

    if(context->error_count == 0){
        return true;
    }
    return false;

}