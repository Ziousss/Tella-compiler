#include "../include/parser/ast.h"
#include "../include/parser/grammarRules.h"
#include "../include/parser/helperFunc.h"

ASTnode *assignParse(Tokenstruct *tokenList, int *index){
    int i = *index;

    //not every expression must be accepted later on
    ASTnode *target = expressionParse(tokenList, &i);
    if(target == NULL){
        return NULL;
    }

    if(tokenList[i].type != TOK_EQ){
        printf("Equal sign expected in assignment line %d\n", tokenList[i].line);
        return NULL;
    } ++i;

    ASTnode *value = expressionParse(tokenList, &i);
    if(value == NULL){
        return NULL;
    }

    if(tokenList[i].type != TOK_SEMICOLON){
        printf("Semicolon expected line %d\n", tokenList[i].line);
        return NULL;
    }
    
    ASTnode *assigneNode = malloc(sizeof(ASTnode));
    if(assigneNode == NULL){
        printf("Malloc error in assignParse.\n");
        return NULL;
    }
    *index = i;
    assigneNode->ast_type = AST_ASSIGN_EXPR;
    assigneNode->data.assign.target = target;
    assigneNode->data.assign.value = value;
    return assigneNode;
}