#include "../include/parser/ast.h"
#include "../include/parser/grammarRules.h"
#include "../include/parser/helperFunc.h"

ASTnode *funcDefParse(Tokenstruct *tokenList, int *index){
    int i = *index;
    
    if(!isTOKType(tokenList[i].type)){
        printf("type expected in the function definition, line %d\n", tokenList[i].line);
        return NULL;
    }
    Tokentype return_type = tokenList[i].type; 
    ++i;

    if(tokenList[i].type != TOK_IDENTIFIER){
        printf("Indentifier expected in the function definition, line %d\n", tokenList[i].line);
        return NULL;
    } 
    int index_identifier = i;
    ++i;

    if(tokenList[i].type != TOK_LPAREN){
        printf(" \"(\" expected in the function definition, line %d\n", tokenList[i].line);
        return NULL;     
    } ++i;

    ParameterNode *parameters = NULL;
    if(tokenList[i].type == TOK_RPAREN){
        ++i;
    } 
    else if(!isTOKType(tokenList[i].type)){
        printf("Missing ')' on line %d in the function definition.\n", tokenList[i].line);
        return NULL;
    }
    else {
        parameters = parameterFuncDefParse(tokenList, &i);
        if (parameters == NULL){
            return NULL;
        }
        if(tokenList[i].type != TOK_RPAREN){
            printf("Right parenthesis expected, line %d\n", tokenList[i].line);
        }++i;
    }

    char *name = strdup(tokenList[index_identifier].lexeme);
    ASTnode *block = blockParse(tokenList, &i, name);

    if (block == NULL){
        free(name);
        return NULL; 
    }

    //all good, we can create the node
    ASTnode *func_def_ast = malloc(sizeof(ASTnode));
    if(func_def_ast == NULL){
        printf("Malloc error in funcDefParse.\n");
        free(name);
        return NULL;
    }
    if(strcmp(name, "main") == 0){
        func_def_ast->ast_type = AST_FUNC_DEF_MAIN;
    } else {
        func_def_ast->ast_type = AST_FUNC_DEF;
    }
    func_def_ast->data.func_def.body = block;
    func_def_ast->data.func_def.name = name;
    func_def_ast->data.func_def.parameters = parameters;
    func_def_ast->data.func_def.return_type = return_type;
    *index = i;

    return func_def_ast;
}