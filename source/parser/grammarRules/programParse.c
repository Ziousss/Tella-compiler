#include "../include/parser/ast.h"
#include "../include/parser/grammarRules.h"
#include "../include/parser/helperFunc.h"

ASTnode *programParse(Tokenstruct *tokenList, int *index){
    int i = *index;
    ASTnode *program = malloc(sizeof(ASTnode));
    if(program == NULL){
        printf("Malloc error in programParse.\n");
        return NULL;
    }
    program->ast_type = AST_PROGRAM;
    program->data.program_node.func_def = NULL;
    program->data.program_node.include = NULL;
    ASTnode **tail_include = &program->data.program_node.include;
    ASTnode **tail_funcDef = &program->data.program_node.func_def;
    while(!isTOKType(tokenList[i].type)){
        ASTnode *include = includeParse(tokenList, &i);
        if(include == NULL){
            return NULL;
        }

        ASTnode *node_include = malloc(sizeof(ASTnode));
        if(node_include == NULL){
            printf("Malloc error in node include, programParse.\n");
            return NULL;
        }
        node_include->data.program_node.include = include;
        node_include->next = NULL;

        *tail_include = node_include;
        tail_include = &node_include->next;
    }


    while(tokenList[i].type != TOK_EOF){
        ASTnode *func_def = funcDefParse(tokenList, &i);
        if(func_def == NULL){
            return NULL;
        }

        ASTnode *node_funcDef = malloc(sizeof(ASTnode));
        if(node_funcDef == NULL){
            printf("Malloc error in node funcDef, programParse.\n");
            return NULL;
        }
        node_funcDef->data.program_node.func_def = func_def;
        node_funcDef->next = NULL;

        *tail_funcDef = node_funcDef;
        tail_funcDef = &node_funcDef->next;
    }

    *index = i;
    prinast(program);
    return program;
}