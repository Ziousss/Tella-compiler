#include "../include/parser/grammarRules.h"

ASTnode *funcCallParse(Tokenstruct *tokenList, int *index){
    int i = *index;
    int start = *index;
    ArgNode *args = NULL;
    ArgNode *last = NULL;
    int name_index = i;
    ASTnode *funcCall = NULL;

    ++i;
    if(tokenList[i].type != TOK_LPAREN){
        return NULL;
    } ++i;

    if(tokenList[i].type == TOK_SEMICOLON){
        printf("Missing a ')' line %ld for the function call file %s\n", tokenList[i].line, tokenList[i].fileName);
        return NULL;
    }
    if (tokenList[i].type == TOK_RPAREN)
    {
        funcCall = malloc(sizeof(ASTnode));
        if (funcCall == NULL){
            printf("Malloc error in funcCall");
            return NULL;
        }
        char *name = strdup(tokenList[name_index].lexeme);
        funcCall->data.func_call.name = name;
        funcCall->ast_type = AST_FUNC_CALL;
        funcCall->data.func_call.args = args;

        return funcCall;
    } else {
        while(true){
            ArgNode *arg = malloc(sizeof(ArgNode));
            ASTnode *expression = expressionParse(tokenList, &i);
            if(expression == NULL){
                printf("Issue in the expressions of function calls line %ld file %s\n", tokenList[i].line, tokenList[i].fileName);
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
                printf("Comma expected in the parameter of the function call line %ld file %s\n", tokenList[i].line, tokenList[i].fileName);
                while(arg != NULL){
                    ArgNode *next = arg->next;
                    free(arg);
                    arg = next;
                }
                free(expression);
                return NULL;
            }

        }
    }++i;

    if(tokenList[i].type != TOK_SEMICOLON){
        free(funcCall);
        printf("Missing semi colon line %ld after the function call of %s file %s\n", tokenList[i].line, tokenList[name_index].lexeme, tokenList[i].fileName);
    } ++i;

    funcCall = malloc(sizeof(ASTnode));
    if (funcCall == NULL){
        printf("Malloc error in funcCall");
        return NULL;
    }

    char *name = strdup(tokenList[name_index].lexeme);
    funcCall->data.func_call.args = args;
    funcCall->ast_type = AST_FUNC_CALL;
    funcCall->data.func_call.name = name;
    funcCall->line = tokenList[start].line;
    funcCall->fileName = strdup(tokenList[start].fileName);
    funcCall->next = NULL;

    *index = i;
    return funcCall;
}