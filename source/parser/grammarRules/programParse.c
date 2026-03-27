#include "../include/parser/grammarRules.h"

ASTnode *programParse(Tokenstruct *tokenList, int *index){
    int i = *index;
    ASTnode *program = malloc(sizeof(ASTnode));
    if(program == NULL){
        printf("Malloc error in programParse.\n");
        return NULL;
    }
    program->ast_type = AST_PROGRAM;
    program->data.program_node.func_def = NULL;
    ASTnode **tail_funcDef = &program->data.program_node.func_def;
    bool main = false;

    while(tokenList[i].type != TOK_EOF){
        ASTnode *func_def = funcDefParse(tokenList, &i);
        if(func_def == NULL){
            return NULL;
        }
        if(func_def->ast_type == AST_FUNC_DEF_MAIN){
            main = true;
        }
        func_def->next = NULL;

        *tail_funcDef = func_def;
        tail_funcDef = &func_def->next;
    }

    if(!main){
        printf("No main function found in the file.\n");
        return NULL;
    }

    *index = i;
    //prinast(program);
    program->next = NULL;
    return program;
}