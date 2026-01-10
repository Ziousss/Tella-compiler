#include "../include/parser/ast.h"
#include "../include/parser/grammarRules.h"
#include "../include/parser/helperFunc.h"

ASTnode *forStmtParse(Tokenstruct *tokenList, int *index){
    int i = *index;

    if(tokenList[i].type != TOK_FOR){
        return NULL;
    } ++i;

    if(tokenList[i].type != TOK_LPAREN){
        printf("'(' expected after the \"for\" line %d\n", tokenList[i].line);
        return NULL;
    } ++i;

    ASTnode *initialisation = declarationParse(tokenList, &i);
    if(initialisation == NULL){
        printf("initialisation issue in for loop.\n");
        return NULL;
    }

    if(tokenList[i].type != TOK_SEMICOLON){
        printf("';' expected in the \"for\" loop line %d\n", tokenList[i].line);
        return NULL;
    } ++i;

    ASTnode *condition = expressionParse(tokenList, &i);
    if(condition == NULL){
        printf("condition issue in for loop.\n");
        return NULL;
    }

    if(tokenList[i].type != TOK_SEMICOLON){
        printf("';' expected in the \"for\" loop line %d\n", tokenList[i].line);
        return NULL;
    } ++i;

    ASTnode *incrementation = expressionParse(tokenList, &i);
    if(incrementation == NULL){
        printf("incrementation issue in for loop.\n");
        return NULL;
    }

    if(tokenList[i].type != TOK_RPAREN){
        printf("')' expected in the \"for\" loop line %d\n", tokenList[i].line);
        return NULL;
    } ++i;

    ASTnode *block = blockParse(tokenList, &i, "for");
    if(block == NULL){
        printf("block issue in for loop.\n");
        return NULL;
    }

    ASTnode *forStmt = malloc(sizeof(ASTnode));
    if(forStmt == NULL){
        printf("Malloc error in the forStmt parser.\n");
        return NULL;
    }
    forStmt->ast_type = AST_FOR_STMT;
    forStmt->data.for_node.block = block;
    forStmt->data.for_node.condition = condition;
    forStmt->data.for_node.incrementation = incrementation;
    forStmt->data.for_node.initialisation = initialisation;

    *index = i;
    return forStmt;
}