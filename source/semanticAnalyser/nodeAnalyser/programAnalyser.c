#include "../include/semanticAnalyser/nodeAnalyser.h"

void programAnalyser(ASTnode *program){
    if(program->ast_type != AST_PROGRAM){
        printf("This is not a program ast, check the given ast.\n");
        return;
    }

    ASTnode *func_def_node = program->data.program_node.func_def;
    ASTnode *tmp = program->data.program_node.func_def;
    while (func_def_node->next != NULL)
    {
        while (func_def_node)
        {
            funcDefAnalyser(func_def_node);
        }
        func_def_node = func_def_node->next;
    } 
}