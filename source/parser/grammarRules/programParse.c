#include "../include/parser/ast.h"
#include "../include/parser/grammarRules.h"
#include "../include/parser/helperFunc.h"

ASTnode *programParse(Tokenstruct *tokenList, int *index){
    int i = *index;
    ASTnode *program = malloc(sizeof(ASTnode));
    program->ast_type = AST_PROGRAM;
    program->data.program_node.func_def = NULL;
    ASTnode **tail = &program->data.program_node.func_def;
    while(true){
        ASTnode *func_call = funcDefParse(tokenList, &i);
        if(func_call == NULL){
            break;
        }

        ASTnode *node = malloc(sizeof(ASTnode));
        node->data.program_node.func_def = func_call;
        node->next = NULL;

        *tail = node;
        tail = &node->next;
    }

    *index = i;
    return program;
}