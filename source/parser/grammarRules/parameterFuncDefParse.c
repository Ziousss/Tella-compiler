#include "../include/parser/grammarRules.h"

ParameterNode *parameterFuncDefParse(Tokenstruct *tokenList, int *index){
    int i = *index;
    int count = 1;
    ParameterNode *param_list = NULL;

    while(true){
        if(!isTOKType(tokenList[i].type)){
            printf("Type expected in the parameter definition line %d, parameter number %d\n", tokenList[i].line, count+1);
            return NULL;
        }
        Tokentype type = tokenList[i].type;
        ++i;

        if(tokenList[i].type != TOK_IDENTIFIER){
            printf("Identifier requiered line %d, parameter number %d\n", tokenList[i].line, count+1);
            return NULL;
        } 
        char *name = strdup(tokenList[i].lexeme);
        ++i;

        ParameterNode *tmp = create_param_tree(name, type, count++);
        param_list_add(&param_list, tmp);

        if(tokenList[i].type == TOK_COMMA){
            ++i;
            continue;
        }
        else if(tokenList[i].type == TOK_RPAREN){
            break;
        }

        if(isTOKType(tokenList[i].type)){
            printf("Expected ',' between arguments %d and %d line %d\n", count, count+1, tokenList[i].line);
        } else {
            printf("Expected ',' or ')' line %d\n", tokenList[i].line);
            return NULL;
        }

    }  
    *index = i;
    ParameterNode *cur = param_list;
    while(cur->next != NULL){
        cur = cur->next;
    }

    param_list->count = cur->count;
    return param_list;
}
