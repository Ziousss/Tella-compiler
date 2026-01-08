#include "../include/parser/ast.h"
#include "../include/parser/grammarRules.h"
#include "../include/parser/helperFunc.h"

ASTnode *ifStmtParse(Tokenstruct *tokenList, int *index){
    int i = *index;
    ASTnode *else_block = NULL;

    //Verification can t hurt xd
    if(tokenList[i].type != TOK_IF){
        return NULL;
    }
    ++i;
    if(tokenList[i].type != TOK_LPAREN){
        printf("'(' expected in the if statement line %d\n", tokenList[i].line);
        return NULL;
    } ++i;

    ASTnode *condition = expressionParse(tokenList, &i);
    if(condition == NULL){
        return NULL;
    }
    
    if(tokenList[i].type != TOK_RPAREN){
        printf("')' expected in the if statement line %d\n", tokenList[i].line);
        return NULL;
    } ++i;

    ASTnode *if_block = blockParse(tokenList, &i);
    if(if_block == NULL){
        return NULL;
    }

    if(tokenList[i].type == TOK_ELSE){
        ++i;
        else_block = blockParse(tokenList, &i);
        if(else_block == NULL){
            printf("else block fails line %d.\n", tokenList[i].line);
            return NULL;
        }
    }

    ASTnode *ifStmt = malloc(sizeof(ASTnode));
    if(ifStmt == NULL){
        printf("Malloc error in ifStmt parser.\n");
        return NULL;
    }
    ifStmt->ast_type = AST_IF_STMT;
    ifStmt->data.if_node.condition = condition;
    ifStmt->data.if_node.if_branch = if_block;
    ifStmt->data.if_node.else_branch = else_block;
    *index = i;
    return ifStmt;
}