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
        printf("Identifier expected line %d after type %s.\n",
               tokenList[i].line, tokenTypeToString(tokenList[i-1].type));
        return NULL;
    }

    int name_i = i;
    ++i;

    // Array declaration
    if(tokenList[i].type == TOK_LSQRTBRAK){
        ++i;
        int number = -1;
        if(tokenList[i].type == TOK_INTEGER_LITERAL){
            number = i;
            ++i;
        } else {
            printf("Integer literal expected for array size line %d.\n", tokenList[i].line);
            return NULL;
        }

        if(tokenList[i].type != TOK_RSQRTBRAK){
            printf("']' expected line %d.\n", tokenList[i].line);
            return NULL;
        }
        ++i;

        if(tokenList[i].type != TOK_SEMICOLON){
            printf("Semicolon expected after array declaration line %d.\n", tokenList[i].line);
            return NULL;
        }
        ++i;

        // Convert to size_t safely
        long long arr_size_ll = atoll(tokenList[number].lexeme);
        if(arr_size_ll < 0){
            printf("Array size cannot be negative line %d.\n", tokenList[number].line);
            return NULL;
        }
        size_t arr_size = (size_t)arr_size_ll;

        ASTnode *arrayDeclation = malloc(sizeof(ASTnode));
        if(!arrayDeclation){
            printf("Malloc failed in declarationParse for arrayDeclation.\n");
            return NULL;
        }

        arrayDeclation->next = NULL;
        arrayDeclation->ast_type = AST_ARRAY_DECL;
        arrayDeclation->data.arrayDecl.name = strdup(tokenList[name_i].lexeme);
        arrayDeclation->data.arrayDecl.type = decla_type;
        arrayDeclation->data.arrayDecl.size = arr_size;
        arrayDeclation->line = tokenList[start].line;

        *index = i;
        return arrayDeclation;
    } 

    // Simple variable declaration
    if(tokenList[i].type == TOK_EQ){
        ++i;
        expression = expressionParse(tokenList, &i);
        if (!expression){
            printf("Expression expected after '=' line %d\n", tokenList[i].line);
            return NULL;
        }
    }

    if(tokenList[i].type != TOK_SEMICOLON){
        printf("Semicolon expected line %d\n", tokenList[i-1].line);
        return NULL;
    }
    ++i;

    char *name = strdup(tokenList[name_i].lexeme);
    declaration = malloc(sizeof(ASTnode));
    if(!declaration){
        printf("Malloc error in declarationParse.\n");
        free(name);
        return NULL;
    }

    declaration->ast_type = AST_VAR_DECL;
    declaration->data.declaration.identifier = name;
    declaration->data.declaration.type = decla_type;
    declaration->data.declaration.expression = expression;
    declaration->next = NULL;
    declaration->line = tokenList[start].line;

    *index = i;
    return declaration;
}