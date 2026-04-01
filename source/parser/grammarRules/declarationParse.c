#include "../include/parser/grammarRules.h"

ASTnode *declarationParse(Tokenstruct *tokenList, int *index){
    int i = *index;
    int start = i;
    //bool is_pointer = false;
    ASTnode *declaration = NULL;
    Tokentype decla_type = tokenList[i].type;
    ASTnode *expression = NULL;
    ++i;

    // Pointer detection
    /*
    if(tokenList[i].type == TOK_STAR){
        is_pointer = true;
        ++i;
    }
    */

    if(tokenList[i].type != TOK_IDENTIFIER){
        printf("Identifier expected line %ld file %s after type %s.\n", tokenList[i].line, tokenList[i].fileName, tokenTypeToString(tokenList[i-1].type));
        return NULL;
    }

    int name_i = i;
    ++i;

    // Array declaration
    if(tokenList[i].type == TOK_LSQRTBRAK){
        ++i;
        ASTnode *size = expressionParse(tokenList, &i);
        if(size == NULL){
            printf("The expression missing is the index for the declaration array on line %ld file %s.\n", tokenList[i].line, tokenList[i].fileName);
            return NULL;
        }

        if(tokenList[i].type != TOK_RSQRTBRAK){
            printf("']' expected line %ld file %s.\n", tokenList[i].line, tokenList[i].fileName);
            return NULL;
        }
        ++i;

        if(tokenList[i].type != TOK_SEMICOLON){
            printf("Semicolon expected after array declaration line %ld file %s.\n", tokenList[i].line, tokenList[i].fileName);
            return NULL;
        }
        ++i;

        ASTnode *arrayDeclation = malloc(sizeof(ASTnode));
        if(!arrayDeclation){
            printf("Malloc failed in declarationParse for arrayDeclation.\n");
            return NULL;
        }

        arrayDeclation->next = NULL;
        arrayDeclation->ast_type = AST_ARRAY_DECL;
        arrayDeclation->data.arrayDecl.name = strdup(tokenList[name_i].lexeme);
        arrayDeclation->data.arrayDecl.type = decla_type;
        arrayDeclation->data.arrayDecl.size = size;
        arrayDeclation->line = tokenList[start].line;
        arrayDeclation->fileName = strdup(tokenList[start].fileName);

        *index = i;
        return arrayDeclation;
    }

    // Simple variable declaration
    if(tokenList[i].type == TOK_EQ){
        ++i;
        expression = expressionParse(tokenList, &i);
        if (!expression){
            printf("Expression expected after '=' line %ld file %s\n", tokenList[i].line, tokenList[i].fileName);
            return NULL;
        }
    }

    if(tokenList[i].type != TOK_SEMICOLON){
        printf("Semicolon expected line %ld file %s\n", tokenList[i-1].line, tokenList[i-1].fileName);
        return NULL;
    }
    ++i;

    declaration = malloc(sizeof(ASTnode));
    if(!declaration){
        printf("Malloc error in declarationParse.\n");
        return NULL;
    }

    char *name = strdup(tokenList[name_i].lexeme);
    declaration->ast_type = AST_VAR_DECL;
    declaration->data.declaration.identifier = name;
    declaration->data.declaration.type = decla_type;
    declaration->data.declaration.expression = expression;
    declaration->next = NULL;
    declaration->line = tokenList[start].line;
    declaration->fileName = strdup(tokenList[start].fileName);

    *index = i;
    return declaration;
}