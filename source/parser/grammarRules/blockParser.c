#include "../include/parser/ast.h"
#include "../include/parser/grammarRules.h"
#include "../include/parser/helperFunc.h"

ASTnode *blockParse(Tokenstruct *tokenList, int *index){
    int i = *index;
    
    if(tokenList[i].type != TOK_LBRACE){
        printf("Expected '{' line %d", tokenList[i].line);
    } ++i;

    ASTnode *stmt_list = NULL;
    ASTnode *last = NULL;
    while (tokenList[i].type != TOK_RBRACE)
    {
        int start_i = i;
        if(tokenList[i].type == TOK_IDENTIFIER){
            ASTnode *func_call = funcCallParse(tokenList, &i);
            if(func_call != NULL){
                add_stmt_list(stmt_list, last, func_call, AST_FUNC_CALL);
                continue;
            }

            ASTnode *assign = assignParse(tokenList, &i);
            if(assign != NULL){
                add_stmt_list(stmt_list,last, assign, AST_ASSIGN_EXPR);
                continue;
            }
        } 
        if(isTOKType(tokenList[i].type)){
            ASTnode *declaration = declarationParse(tokenList, &i);
            if(declaration != NULL){
                add_stmt_list(stmt_list, last, declaration, AST_VAR_DECL);
                continue;
            }
        }
        if(tokenList[i].type == TOK_IF){
            ASTnode *if_stmt = ifStmtParse(tokenList, &i);
            if(if_stmt == NULL){
                return NULL;
            }
            add_stmt_list(stmt_list, last, if_stmt, AST_IF_STMT);
            continue;
        }
        if(tokenList[i].type == TOK_FOR){
            ASTnode *for_stmt = forStmtParse(tokenList, &i);
            if(for_stmt == NULL){
                return NULL;
            }
            add_stmt_list(stmt_list, last, for_stmt, AST_FOR_STMT);
            continue;
        }
        if(tokenList[i].type == TOK_WHILE){
            ASTnode *while_stmt = whileStmtParse(tokenList, &i);
            if(while_stmt == NULL){
                return NULL;
            }
            add_stmt_list(stmt_list, last, while_stmt, AST_WHILE_STMT);
            continue;
        }  
        if(tokenList[i].type == TOK_RETURN){
            ASTnode *return_stmt = returnStmtParse(tokenList, &i);
            if(return_stmt == NULL){
                return NULL;
            }
            add_stmt_list(stmt_list, last, return_stmt, AST_RETURN);
            continue;
        }  
        if (i == start_i) {
            printf("Unexpected token '%s' in block at line %d\n or error if error message.",tokenTypeToString(tokenList[i].type), tokenList[i].line);
            return NULL;
        }
    }
    ++i;
    *index = i;
    return stmt_list;
}