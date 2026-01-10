#include "../include/parser/ast.h"
#include "../include/parser/grammarRules.h"
#include "../include/parser/helperFunc.h"

ASTnode *includeParse(Tokenstruct *tokenList, int *index){
    int i = *index;

    int name_header;
    if(tokenList[i].type != TOK_HASHTAG){
        if(tokenList[i].type == TOK_INCLUDE){
            printf("Hashtag needed line %d in front of the include statement.\n", tokenList[i].line);
        }
        return NULL;
    } ++i;

    if(tokenList[i].type != TOK_INCLUDE){
        printf("Hashtag present on line %d. To include a header file, write '#include <header.h>' header being the name of the file.\n", tokenList[i].line);
        return NULL;
    } ++i;

    if(tokenList[i].type == TOK_LESS){
        ++i;

        if(tokenList[i].type != TOK_INCLUDE_NAME){
            printf("Header_file needed between the '<' and '>' characters line %d.\n", tokenList[i].line);
            return NULL;
        } 
        name_header = i;
        ++i;

        if(tokenList[i].type != TOK_GR){
            printf("Missing '>' character in the include statement line %d.\n", tokenList[i].line);
            return NULL;
        } ++i;
    }  
    else if(tokenList[i].type == TOK_QUOTE ){
        ++i;

        if(tokenList[i].type != TOK_LOCAL_INCLUDE){
            printf("Expected local include between two quotes line %d.\n", tokenList[i].line);
            return NULL;
        }
        name_header = i;
        ++i;

        if(tokenList[i].type != TOK_QUOTE){
            printf("Expected quote at the end of the include statement line %d.\n", tokenList[i].line);
            return NULL;
        }++i;

    }
    else{
        printf("None conform header file in the include statement line %d. Could be mising the quotes if it is a local file.\n", tokenList[i].line);
        return NULL;
    }

    ASTnode *include = malloc(sizeof(ASTnode));
    if(include == NULL){
        printf("Malloc error in includeParse.\n");
        return NULL;
    }

    //this makes the whole thing crash
    char *name = strdup(tokenList[name_header].lexeme);

    include->ast_type = AST_INCLUDE;
    include->data.include_node.name = name;

    *index = i;
    return include;
}