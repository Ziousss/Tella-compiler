#include "../include/parser/ast.h"
#include "../include/parser/grammarRules.h"
#include "../include/parser/helperFunc.h"

ASTnode *programParse(Tokenstruct *tokenList, int *index){
    int i = *index;
    ASTnode *program = malloc(sizeof(ASTnode));
    program->ast_type = AST_PROGRAM;
    program->data.program_node.func_def = NULL;
    ASTnode **tail = &program->data.program_node.func_def;
    while(tokenList[i].type != TOK_EOF){
        ASTnode *func_def = funcDefParse(tokenList, &i);
        if(func_def == NULL){
            return NULL;
        }

        ASTnode *node = malloc(sizeof(ASTnode));
        node->data.program_node.func_def = func_def;
        node->next = NULL;

        *tail = node;
        tail = &node->next;
    }

    *index = i;
    //debugging
    printf("Returning programParse\n");
    prinast(program);
    return program;
}