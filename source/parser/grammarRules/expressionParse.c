#include "../include/parser/ast.h"
#include "../include/parser/grammarRules.h"
#include "../include/parser/helperFunc.h"

ASTnode *expressionParse(Tokenstruct *tokenList, int *index){
    int i = *index;
    ASTnode *left = NULL;

    if(tokenList[i].type == TOK_IDENTIFIER){
        char *name = strdup(tokenList[i].lexeme);
        int tmp = i;
        ASTnode *function_call = funcCallParseExpression(tokenList, &i);
        if(function_call != NULL){
            left = function_call;
        } 
        else if(tokenList[++tmp].type == TOK_LPAREN){
            //FuncCall NULL but it s not an indentifier
            return NULL;
        }
        else{
            left = malloc(sizeof(ASTnode));
            if(left == NULL){
                printf("Malloc error in expression parser (operator)\n");
                free(name);
                return NULL;
            }
            ++i;
            left->ast_type = AST_IDENTIFIER;
            left->data.identifier.name = name;
        }
    }
    else if(tokenList[i].type == TOK_INTEGER_LITERAL){
        left = malloc(sizeof(ASTnode));
        if(left == NULL){
            printf("Malloc error in expression parser (operator)\n");
            return NULL;
        }
        left->ast_type = AST_NUMBER;
        left->data.int_literal.value = atoi(tokenList[i].lexeme);
        ++i;
    }
    else if(tokenList[i].type == TOK_LPAREN){
        ++i; 
        left = expressionParse(tokenList, &i);
        if(left == NULL){
            return NULL;
        }
        if(tokenList[i].type != TOK_RPAREN){
            printf("')' expected in expression line %d\n", tokenList[i].line);
            return NULL;
        }
        ++i;
    } 
    else {
        printf("expression expected line %d\n", tokenList[i].line);
        return NULL;
    }

    if(isOperatorExpression(tokenList[i].type)){
        //wrong for calculation for now but we ll let it be and change it later
        Tokentype op = tokenList[i].type;
        ++i; 
        ASTnode *right = expressionParse(tokenList, &i);
        if(right == NULL){
            return NULL;
        }

        ASTnode *tmp = malloc(sizeof(ASTnode));
        if(tmp == NULL){
            printf("Malloc error in expression parser (operator)\n");
            return NULL;
        }
        
        tmp->ast_type = AST_BINARY_EXPR;
        tmp->data.binary.left = left;
        tmp->data.binary.right = right;
        tmp->data.binary.op = op;
        
        left = tmp;
    }

    *index = i;
    return left;
}