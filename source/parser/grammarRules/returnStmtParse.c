#include "../include/parser/ast.h"
#include "../include/parser/grammarRules.h"
#include "../include/parser/helperFunc.h"

ASTnode *returnStmtParse(Tokenstruct *tokenList, int *index){
    int i = *index;
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
        printf("Expected semicolon after return expression line %d\n", tokenList[i].line);
        return NULL;
    } ++i;

    ASTnode *returnStmt = malloc(sizeof(ASTnode));
    if(returnStmt == NULL){
        printf("Malloc error in the return parsign.\n");
        return NULL;
    }
    returnStmt->data.return_node.expr = expression;
    returnStmt->ast_type = AST_RETURN;

    *index = i;
    return returnStmt;
}