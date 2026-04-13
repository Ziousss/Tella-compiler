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
    ASTnode *node = program->data.program_node.func_def;
    while (node != NULL)
    {
        if(node->ast_type == AST_FUNC_DEF || node->ast_type == AST_FUNC_DEF_MAIN){
            funcDefAnalyser(node, context);
        } else if (node->ast_type == AST_FUNC_SIGN){
            funcSignAnalyser(node, context);
        }
        node = node->next;
    } 

    GlobalFunc *functionsList = getAllFunctions(context);
    if(functionsList == NULL){
        printf("FunctionList is NULL\n");
        return NULL;
    } else if(context->error_count != 0){
        printf("%d errors in the semantic analyser.\n", context->error_count);
        return NULL;
    }

    GlobalFunc *current = functionsList;
    while (current != NULL)
    {
        current->sym = context->IRsym;
        current = current->next;
    }

    ScopeNode *cur = context->current_scope;
    while(cur != NULL){
        SymbolNode *nodeSym = cur->symbols;
        while(nodeSym != NULL){
            SymbolNode *next = nodeSym->next;
            free(nodeSym);
            nodeSym = next;
        }
        ScopeNode *next = cur->parent;
        free(cur);
        cur = next;
    }
    
    free(context);
    return functionsList;
}