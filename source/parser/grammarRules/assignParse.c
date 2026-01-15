#include "../include/parser/grammarRules.h"

ASTnode *assignParse(Tokenstruct *tokenList, int *index){
    int i = *index;
    int start = *index;

    if(tokenList[i].type != TOK_IDENTIFIER){
        printf("Left side of the assignment line %d must be a defined identifier.\n", tokenList[i].line);
        return NULL;
    }
    int identifier_name = i;
    ++i;

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

    char *name = strdup(tokenList[identifier_name].lexeme); 
    assigneNode->ast_type = AST_ASSIGN_EXPR;
    assigneNode->data.assign.target = name;
    assigneNode->data.assign.value = value;
    assigneNode->line = tokenList[start].line;
    *index = i;
    return assigneNode;
}