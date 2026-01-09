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
        printf("indentifier expected in the function definition, line %d\n", tokenList[i].line);
        return NULL;
    } 
    char *name = strdup(tokenList[i].lexeme);
    ++i;

    if(tokenList[i].type != TOK_LPAREN){
        printf(" \"(\" expected in the function definition, line %d\n", tokenList[i].line);
        return NULL;     
    } ++i;
    
    ParameterNode *parameters = NULL;
    if(tokenList[i].type == TOK_RPAREN){
        ++i;
    } else {
        parameters = parameterFuncDefParse(tokenList, &i);
        if (parameters == NULL){
            return NULL;
        }
        if(tokenList[i].type != TOK_RPAREN){
            printf("Right parenthesis expected, line %d\n", tokenList[i].line);
        }++i;
    }

    ASTnode *block = blockParse(tokenList, &i);

    if (block == NULL){
        return NULL; 
    }

    //all good, we can create the node
    ASTnode *func_def_ast = malloc(sizeof(ASTnode));
    func_def_ast->ast_type = AST_FUNC_DEF;
    func_def_ast->data.func_def.body = block;
    func_def_ast->data.func_def.name = name;
    func_def_ast->data.func_def.parameters = parameters;
    func_def_ast->data.func_def.return_type = return_type;
    *index = i;

    //debugging
    printf("Returning FuncDefParse\n");    
    return func_def_ast;
}