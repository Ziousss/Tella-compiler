#include "../include/parser/ast.h"
#include "../include/parser/grammarRules.h"
#include "../include/parser/helperFunc.h"

ASTnode *declarationParse(Tokenstruct *tokenList, int *index){
    int i = *index;
    ASTnode *declaration = NULL;
    Tokentype decla_type = tokenList[i].type;
    ASTnode *expression = NULL;
    ++i;

    if(tokenList[i].type != TOK_IDENTIFIER){
        printf("Identifier expected line %d", tokenList[i].line);
        return NULL;
    }
    int name_i = i;
    ++i;

    if(tokenList[i].type == TOK_EQ){
        ++i;
        expression = expressionParse(tokenList, &i);
        if (expression == NULL){
            printf("expression expected after '=' line %d", tokenList[i].line);
            return NULL;
        }
    }

    if(tokenList[i].type != TOK_SEMICOLON){
        printf("Semicolon expected line %d", tokenList[i].line);
        return NULL;
    } ++i;

    char *name = strdup(tokenList[name_i].lexeme);

    *index = i;
    declaration = malloc(sizeof(ASTnode));
    declaration->ast_type = AST_VAR_DECL;
    declaration->data.declaration.expression = expression;
    declaration->data.declaration.identifier = name;
    declaration->data.declaration.type = decla_type;

    return declaration;
}