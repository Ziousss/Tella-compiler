#include "../include/parser/grammarRules.h"

ASTnode *funcDefParse(Tokenstruct *tokenList, int *index){
    int i = *index;
    int start = *index;

    if(!isTOKType(tokenList[i].type)){
        printf("type expected in the function definition, line %ld file %s\n", tokenList[i].line, tokenList[i].fileName);
        return NULL;
    }
    Tokentype return_type = tokenList[i].type; 
    ++i;

    if(tokenList[i].type != TOK_IDENTIFIER){
        printf("Indentifier expected in the function definition, line %ld file %s\n", tokenList[i].line, tokenList[i].fileName);
        return NULL;
    } 
    int index_identifier = i;
    ++i;

    if(tokenList[i].type != TOK_LPAREN){
        printf(" \"(\" expected in the function definition, line %ld file %s\n", tokenList[i].line, tokenList[i].fileName);
        return NULL;     
    } ++i;

    bool param = true;
    ParameterNode *parameters = NULL;
    if(tokenList[i].type == TOK_RPAREN){
        ++i;
    } 
    else if(!isTOKType(tokenList[i].type) && tokenList[i].type != TOK_IDENTIFIER){
        printf("Missing ')' on line %ld file %s in the function definition.\n", tokenList[i].line, tokenList[i].fileName);
        return NULL;
    } else {
        parameters = parameterFuncDefParse(tokenList, &i);
        if (parameters == NULL){
            return NULL;
        }
        if(tokenList[i].type != TOK_RPAREN){
            printf("Right parenthesis expected, line %ld file %s\n", tokenList[i].line, tokenList[i].fileName);
        }++i;
    }

    if(tokenList[i].type == TOK_SEMICOLON){
        ++i; 
        ASTnode *func_def_ast = malloc(sizeof(ASTnode));
        if(func_def_ast == NULL){
            printf("Malloc error in funcDefParse.\n");
            return NULL;
        }
        
        char *name = strdup(tokenList[index_identifier].lexeme);

        func_def_ast->ast_type = AST_FUNC_SIGN;
        func_def_ast->data.func_def.body = NULL;
        func_def_ast->data.func_def.name = name;
        func_def_ast->data.func_def.parameters = parameters;
        func_def_ast->data.func_def.param = param;
        func_def_ast->data.func_def.return_type = return_type;
        func_def_ast->line = tokenList[start].line;
        func_def_ast->fileName = strdup(tokenList[start].fileName);
        func_def_ast->next = NULL;

        *index = i;
        return func_def_ast;
    }

    ASTnode *block = blockParse(tokenList, &i);

    if (block == NULL){
        return NULL; 
    }

    //all good, we can create the node
    ASTnode *func_def_ast = malloc(sizeof(ASTnode));
    if(func_def_ast == NULL){
        printf("Malloc error in funcDefParse.\n");
        return NULL;
    }
    
    char *name = strdup(tokenList[index_identifier].lexeme);
    if(strcmp(name, "main") == 0){
        func_def_ast->ast_type = AST_FUNC_DEF_MAIN;
    } else {
        func_def_ast->ast_type = AST_FUNC_DEF;
    }

    func_def_ast->data.func_def.body = block;
    func_def_ast->data.func_def.name = name;
    func_def_ast->data.func_def.parameters = parameters;
    func_def_ast->data.func_def.param = param;
    func_def_ast->data.func_def.return_type = return_type;
    func_def_ast->line = tokenList[start].line;
    func_def_ast->fileName = strdup(tokenList[start].fileName);
    func_def_ast->next = NULL;

    *index = i;
    return func_def_ast;
}