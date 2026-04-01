#include "../include/parser/grammarRules.h"

ASTnode *returnStmtParse(Tokenstruct *tokenList, int *index){
    int i = *index;
    int start = *index;
    ASTnode *expression = NULL;
    if (tokenList[i].type != TOK_RETURN){
        return NULL;
    }++i;

    if(tokenList[i].type != TOK_SEMICOLON){
        expression = expressionParse(tokenList, &i);
        if(expression == NULL){
            printf("Issue in the return adress expression.\n");
            return NULL;
        }
    }

    if(tokenList[i].type != TOK_SEMICOLON){
        printf("Expected semicolon after return expression line %ld file %s\n", tokenList[i].line, tokenList[i].fileName);
        return NULL;
    } ++i;

    ASTnode *returnStmt = malloc(sizeof(ASTnode));
    if(returnStmt == NULL){
        printf("Malloc error in the return parsign.\n");
        return NULL;
    }
    returnStmt->data.return_node.expr = expression;
    returnStmt->ast_type = AST_RETURN;
    returnStmt->line = tokenList[start].line;
    returnStmt->fileName = strdup(tokenList[start].fileName);
    returnStmt->next = NULL;

    *index = i;
    return returnStmt;
}