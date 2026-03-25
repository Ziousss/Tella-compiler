#include "../include/parser/grammarRules.h"

ASTnode *funcCallParseExpression(Tokenstruct *tokenList, int *index){
    int i = *index;
    int start = *index;
    ArgNode *args = NULL;
    ArgNode *last = NULL;
    ASTnode *funcCall = malloc(sizeof(ASTnode));
    if (funcCall == NULL){
        printf("Malloc error in funcCall");
        return NULL;
    }
    ++i;
    if(tokenList[i].type != TOK_LPAREN){
        free(funcCall);
        return NULL;
    } ++i;

    if(tokenList[i].type == TOK_SEMICOLON){
        printf("Missing a ')' line %d for the function call\n", tokenList[i].line);
        free(funcCall);
        return NULL;
    }
    if (tokenList[i].type == TOK_RPAREN)
    {
        char *name = strdup(tokenList[start].lexeme);
        funcCall->data.func_call.name = name;
        funcCall->ast_type = AST_FUNC_CALL;
        funcCall->data.func_call.args = args;
        funcCall->line = tokenList[start].line;
    } else {
        while(true){
            ArgNode *arg = malloc(sizeof(ArgNode));
            ASTnode *expression = expressionParse(tokenList, &i);
            if(expression == NULL){
                printf("Issue in the expressions of function calls line %d\n", tokenList[i].line);
                return NULL;
            }
            arg->expression = expression;
            arg->next = NULL;

            if(!args){
                args = arg;
            } else {
                last->next = arg;
            }
            last = arg;
            
            if (tokenList[i].type == TOK_COMMA) {
                i++;
                continue;
            }

            if (tokenList[i].type == TOK_RPAREN){
                break;
            }

            if(tokenList[i].type != TOK_COMMA){
                printf("Comma expected in the parameter of the function call line %d\n", tokenList[i].line);
                free(arg);
                free(expression);
                free(funcCall);
                return NULL;
            }

        }
    }++i;

    char *name = strdup(tokenList[start].lexeme);
    funcCall->data.func_call.args = args;
    funcCall->ast_type = AST_FUNC_CALL;
    funcCall->data.func_call.name = name;
    funcCall->line = tokenList[start].line;
    funcCall->next = NULL;

    *index = i;
    return funcCall;
}