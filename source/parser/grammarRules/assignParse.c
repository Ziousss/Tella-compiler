#include "../include/parser/grammarRules.h"

ASTnode *assignParse(Tokenstruct *tokenList, int *index){
    int i = *index;
    int start = *index;

    if(tokenList[i].type != TOK_IDENTIFIER){
        printf("Left side of the assignment line %ld file %s must be a defined identifier.\n", tokenList[i].line, tokenList[i].fileName);
        return NULL;
    }
    int identifier_name = i;
    ++i;

    if(tokenList[i].type == TOK_LSQRTBRAK){
        ++i;
        ASTnode *assignArr = assignArrayParse(tokenList, &i, identifier_name);
        if(assignArr == NULL){
            return NULL;
        }

        *index = i;
        return assignArr;
    }

    if(tokenList[i].type != TOK_EQ && tokenList[i].type != TOK_PLUSEQ && tokenList[i].type != TOK_PLUSPLUS && tokenList[i].type != TOK_MINUSEQ && tokenList[i].type != TOK_MINUSMINUS){
        if(tokenList[i].line != tokenList[i-1].line){
            printf("Equal sign expected in assignment line %ld file %s\n", tokenList[i-1].line, tokenList[i-1].fileName);
            return NULL;
        } 
        printf("Equal sign expected in assignment line %ld file %s\n", tokenList[i].line, tokenList[i-1].fileName);
        return NULL;
    } 
    int tok = i;
    ++i;

    
    ASTnode *value = NULL;
    if(tokenList[tok].type != TOK_PLUSPLUS && tokenList[tok].type != TOK_MINUSMINUS){
        value = expressionParse(tokenList, &i);
        if(value == NULL){
            return NULL;
        }
    } else {
        value = malloc(sizeof(ASTnode));
        if(value == NULL){
            printf("Malloc error in assignParse for value.\n");
            return NULL;
        }

        value->ast_type = AST_NUMBER;
        value->data.int_literal.value = 1;
        value->fileName = strdup(tokenList[i].fileName);
        value->line = tokenList[i].line;

        value->next = NULL;
    }

    ASTnode *givenvalue = NULL;
    if(tokenList[tok].type == TOK_PLUSEQ || tokenList[tok].type == TOK_PLUSPLUS || tokenList[tok].type == TOK_MINUSEQ || tokenList[tok].type == TOK_MINUSMINUS){
        ASTnode *expression = malloc(sizeof(ASTnode));
        if(expression == NULL){
            printf("Malloc error in assignParse for expression.\n");
            return NULL;
        }

        ASTnode *identifier = malloc(sizeof(ASTnode));
        if(identifier == NULL){
            free(expression);
            printf("Malloc error in assignParse for identifier.\n");
            return NULL;
        }

        identifier->ast_type = AST_IDENTIFIER;
        identifier->data.identifier.name = strdup(tokenList[identifier_name].lexeme);
        identifier->next = NULL;
        identifier->fileName = strdup(tokenList[i].fileName);
        identifier->line = tokenList[i].line;

        expression->ast_type = AST_BINARY_EXPR;
        expression->data.binary.left = identifier;
        if(tokenList[tok].type == TOK_PLUSEQ || tokenList[tok].type == TOK_PLUSPLUS) expression->data.binary.op = TOK_PLUS;
        else expression->data.binary.op = TOK_MINUS;
        expression->data.binary.right = value;
        expression->next = NULL;
        expression->fileName = strdup(tokenList[i].fileName);
        expression->line = tokenList[i].line;

        givenvalue = expression;
    } else {
        givenvalue = value;
    }
    givenvalue->next = NULL;

    if(tokenList[i].type != TOK_SEMICOLON){
        // -1 so it does not do +1 in case the ith token is on  a new line, this expects people to write the assignement on the same line. 
        if(tokenList[i].line != tokenList[i-1].line){
            printf("Semi-collon expected in assignment line %ld file %s\n", tokenList[i-1].line, tokenList[i-1].fileName);
            return NULL;
        } 
        printf("Semi-collon expected in assignment line %ld file %s\n", tokenList[i].line, tokenList[i].fileName);
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
    assigneNode->data.assign.value = givenvalue;
    assigneNode->line = tokenList[start].line;
    assigneNode->fileName = strdup(tokenList[start].fileName);
    assigneNode->next = NULL;
    *index = i;
    return assigneNode;
}