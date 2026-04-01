#include "../include/parser/grammarRules.h"

ASTnode *whileStmtParse(Tokenstruct *tokenList, int *index){
    int i = *index;
    int start = *index;

    if(tokenList[i].type != TOK_WHILE){
        return NULL;
    } ++i;

    if(tokenList[i].type != TOK_LPAREN){
        printf("'(' expected after while line %ld file %s\n", tokenList[i].line, tokenList[i].fileName);
        return NULL;
    }++i;

    ASTnode *condition = expressionParse(tokenList, &i);
    if(condition == NULL){
        printf("Issue with the while condition in line %ld file %s, the wrong token is %s\n", tokenList[i].line, tokenList[i].fileName, tokenTypeToString(tokenList[i].type));
        return NULL;
    }

    if(tokenList[i].type != TOK_RPAREN){
        printf("')' expected after the while condition line %ld file %s\n", tokenList[i].line,tokenList[i].fileName);
        return NULL;
    }++i;

    ASTnode *block = blockParse(tokenList, &i);
    if(block == NULL){
        printf("Issue in the block parsing of the while statement.\n");
        return NULL;
    }

    ASTnode *whileStmt = malloc(sizeof(ASTnode));
    if(whileStmt == NULL){
        printf("Malloc error in while parsing.\n");
        return NULL;
    }
    whileStmt->data.while_node.block = block;
    whileStmt->data.while_node.condition = condition;
    whileStmt->ast_type = AST_WHILE_STMT;
    whileStmt->line = tokenList[start].line;
    whileStmt->fileName = strdup(tokenList[start].fileName);
    whileStmt->next = NULL;

    *index = i;
    return whileStmt;
}