#include "../include/parser/ast.h"
#include "../include/parser/grammarRules.h"
#include "../include/parser/helperFunc.h"

ParameterNode *parameterParse(Tokenstruct *tokenList, int *index){
    int i = *index;
    int count = 0;
    ParameterNode *param_list = NULL;

    while(true){
        if(!isTOKType(tokenList[i].type)){
            printf("Type expected in the parameter defenition line %d", tokenList[i].line);
            return NULL;
        }
        Tokentype type = tokenList[i].type;
        ++i;

        if(tokenList[i].type != TOK_IDENTIFIER){
            printf("Identifier requiered line %d", tokenList[i].line);
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
        
        printf("Expected ',' or ')' line %d", tokenList[i].line);
        return NULL;
    }  
    *index = i;
    return param_list;
}
