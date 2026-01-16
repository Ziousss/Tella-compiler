#include "../include/parser/grammarRules.h"

ASTnode *expressionParse(Tokenstruct *tokenList, int *index){
    int i = *index;
    int start = *index;
    ASTnode *left = NULL;

    if(tokenList[i].type == TOK_IDENTIFIER){
        char *name = strdup(tokenList[i].lexeme);
        ASTnode *function_call = funcCallParseExpression(tokenList, &i);
        if(function_call != NULL){
            left = function_call;
        } 
        else if(tokenList[i+1].type == TOK_LPAREN){
            //FuncCall NULL but it s not an indentifier
            free(name);
            return NULL;
        }
        else{
            left = malloc(sizeof(ASTnode));
            if(left == NULL){
                printf("Malloc error in expression parser (identifier)\n");
                free(name);
                return NULL;
            }
            ++i;
            left->ast_type = AST_IDENTIFIER;
            left->data.identifier.name = name;
            left->line = tokenList[start].line;
        }
    }
    else if(tokenList[i].type == TOK_INTEGER_LITERAL){
        left = malloc(sizeof(ASTnode));
        if(left == NULL){
            printf("Malloc error in expression parser (integer_literal)\n");
            return NULL;
        }
        left->ast_type = AST_NUMBER;
        left->data.int_literal.value = atoi(tokenList[i].lexeme);
        left->line = tokenList[start].line;
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
    else if(tokenList[i].type == TOK_CHAR_LITERAL){
        left = malloc(sizeof(ASTnode));
        if(left == NULL){
            printf("Malloc error in expression parser (char_literal)\n");
            return NULL;
        }
        char chr = tokenList[i].lexeme[0];
        left->ast_type = AST_CHAR_LITERAL;
        left->data.character_literal.character = chr;
        left->line = tokenList[start].line;
        ++i;
    }
    else if(tokenList[i].type == TOK_STRING_LITERAL){
        left = malloc(sizeof(ASTnode));
            if(left == NULL){
                printf("Malloc error in expression parser (string_literal)\n");
                return NULL;
            }
        char *string = strdup(tokenList[i].lexeme);
        left->ast_type = AST_STRING_LITERAL;
        left->data.string_literal.string = string;
        left->line = tokenList[start].line;
        ++i;
    }
    else if(tokenList[i].type == TOK_TRUE || tokenList[i].type == TOK_FALSE){
        left = malloc(sizeof(ASTnode));
            if(left == NULL){
                printf("Malloc error in expression parser (string_literal)\n");
                return NULL;
            }
        left->ast_type = AST_BOOLEAN;
        if(tokenList[i].type == TOK_TRUE){
            left->data.boolean_literal.boolean = true;
        } else {
            left->data.boolean_literal.boolean = false;
        }
        left->line = tokenList[start].line;
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
        tmp->line = tokenList[start].line;
        left = tmp;
    }

    *index = i;
    return left;
}