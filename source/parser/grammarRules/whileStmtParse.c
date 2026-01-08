#include "../include/parser/ast.h"
#include "../include/parser/grammarRules.h"
#include "../include/parser/helperFunc.h"

ASTnode *whileStmtParse(Tokenstruct *tokenList, int *index){
    int i = *index;

    if(tokenList[i].type != TOK_WHILE){
        return NULL;
    } ++i;

    if(tokenList[i].type != TOK_LPAREN){
        printf("'(' expected after while line %d\n", tokenList[i].line);
        return NULL;
    }++i;

    ASTnode *condition = expressionParse(tokenList, &i);
    if(condition == NULL){
        printf("Issue with the expression condition in line %d\n", tokenList[i].line);
        return NULL;
    }

    if(tokenList[i].type != TOK_RPAREN){
        printf("')' expected after the while condition line %d\n", tokenList[i].line);
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
    *index = i;
    whileStmt->data.while_node.block = block;
    whileStmt->data.while_node.condition = condition;
    whileStmt->ast_type = AST_WHILE_STMT;
    return whileStmt;
}