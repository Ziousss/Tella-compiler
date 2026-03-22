#include "../include/parser/grammarRules.h"

ASTnode *assignArray(Tokenstruct *tokenList, int *index, int nameNumber){
    int i = *index;
    int start = i;

    ASTnode *arrIndex = expressionParse(tokenList, &i);
    if(arrIndex == NULL){
        return NULL;
    }

    if(tokenList[i].type != TOK_RSQRTBRAK){
        printf("']' expected in the array assignment line %d.\n", tokenList[i].line);
        return NULL;
    }i++;

    if(tokenList[i].type != TOK_EQ){
        printf("'=' expected in the array assignment line %d.\n", tokenList[i].line);
        return NULL;   
    }i++;

    ASTnode *value = expressionParse(tokenList, &i);
    if(value == NULL){
        return NULL;
    }

    if(tokenList[i].type != TOK_SEMICOLON){
        printf("';' expected in the array assignment line %d.\n", tokenList[i].line);
        return NULL;
    }i++;

    ASTnode *array = malloc(sizeof(ASTnode));
    if(array == NULL){
        printf("Malloc failed in the assignArray.\n");
        return NULL;
    }

    char *name = strdup(tokenList[nameNumber].lexeme);
    array->next = NULL;
    array->line = start;
    array->ast_type = AST_ASSIGN_ARRAY;
    array->data.arrayAssign.name = name;
    array->data.arrayAssign.value = value;
    array->data.arrayAssign.index = arrIndex;
    
    *index = i;
    return array;
}