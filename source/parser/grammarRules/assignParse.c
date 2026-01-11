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
        if(tokenList[i].line != tokenList[i-1].line){
            printf("Equal sign expected in assignment line %d\n", tokenList[i-1].line);
            return NULL;
        } 
        printf("Equal sign expected in assignment line %d\n", tokenList[i].line);
        return NULL;
    } ++i;

    ASTnode *value = expressionParse(tokenList, &i);
    if(value == NULL){
        return NULL;
    }

    if(tokenList[i].type != TOK_SEMICOLON){
        // -1 so it does not do +1 in case the ith token is on  a new line, this expects people to write the assignement on the same line. 
        if(tokenList[i].line != tokenList[i-1].line){
            printf("Equal sign expected in assignment line %d\n", tokenList[i-1].line);
            return NULL;
        } 
        printf("Equal sign expected in assignment line %d\n", tokenList[i].line);
        return NULL;
    }++i;

    ASTnode *assigneNode = malloc(sizeof(ASTnode));
    if(assigneNode == NULL){
        printf("Malloc error in assignParse.\n");
        return NULL;
    }

    assigneNode->ast_type = AST_ASSIGN_EXPR;
    assigneNode->data.assign.target = target;
    assigneNode->data.assign.value = value;

    *index = i;
    return assigneNode;
}