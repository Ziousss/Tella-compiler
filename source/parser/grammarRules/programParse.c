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
    //Include is just for fun not actually doing it for now
    //program->data.program_node.include = NULL;
    //ASTnode **tail_include = &program->data.program_node.include;
    ASTnode **tail_funcDef = &program->data.program_node.func_def;
    bool main = false;
    /*
    This is old design as well xD
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
    */

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
    prinast(program);
    return program;
}