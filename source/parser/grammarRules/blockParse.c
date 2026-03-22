#include "../include/parser/grammarRules.h"

ASTnode *blockParse(Tokenstruct *tokenList, int *index){
    int i = *index;
    
    if(tokenList[i].type != TOK_LBRACE){
        if(tokenList[i].line == tokenList[i-1].line){
            printf("Expected '{' line %d\n", tokenList[i].line);
            return NULL;
        }
        printf("Expected '{' line %d\n", tokenList[i-1].line);
        return NULL;
    } ++i;

    ASTnode *stmt_list = NULL;
    ASTnode *last = NULL;
    if(tokenList[i].type == TOK_RBRACE){
        i++;

        ASTnode *block = malloc(sizeof(ASTnode));
        if(block==NULL){
            printf("Error malloc in block parser empty function.\n");
            return NULL;
        }
        block->ast_type = AST_BLOCK;
        block->data.block.stmts = NULL;
        block->next = NULL;

        *index = i;
        return block;
    } else {
        while (tokenList[i].type != TOK_RBRACE)
        {
            int start_i = i;
            if(tokenList[i].type == TOK_IDENTIFIER){
                int tmp = i;
                if(tokenList[tmp + 1].type == TOK_LPAREN){
                    ASTnode *func_call = funcCallParse(tokenList, &i);
                    if(func_call != NULL){
                        add_stmt_list(&stmt_list, &last, func_call, AST_FUNC_CALL);
                        continue;
                    }
                } else {
                    ASTnode *assign = assignParse(tokenList, &i);
                    if(assign != NULL){
                        add_stmt_list(&stmt_list,&last, assign, assign->ast_type);
                        continue;
                    }
                }
            } 
            if(isTOKType(tokenList[i].type)){
                ASTnode *declaration = declarationParse(tokenList, &i);
                if(declaration != NULL){
                    add_stmt_list(&stmt_list,&last, declaration, declaration->ast_type);
                    continue;
                }   
            }
            if(tokenList[i].type == TOK_IF){
                ASTnode *if_stmt = ifStmtParse(tokenList, &i);
                if(if_stmt == NULL){
                    return NULL;
                }
                add_stmt_list(&stmt_list,&last, if_stmt, AST_IF_STMT);
                continue;
            }
            if(tokenList[i].type == TOK_FOR){
                ASTnode *for_stmt = forStmtParse(tokenList, &i);
                if(for_stmt == NULL){
                    return NULL;
                }
                add_stmt_list(&stmt_list,&last, for_stmt, AST_FOR_STMT);
                continue;
            }
            if(tokenList[i].type == TOK_WHILE){
                ASTnode *while_stmt = whileStmtParse(tokenList, &i);
                if(while_stmt == NULL){
                    return NULL;
                }
                add_stmt_list(&stmt_list,&last, while_stmt, AST_WHILE_STMT);
                continue;
            }  
            if(tokenList[i].type == TOK_RETURN){
                ASTnode *return_stmt = returnStmtParse(tokenList, &i);
                if(return_stmt == NULL){
                    return NULL;
                }
                add_stmt_list(&stmt_list,&last, return_stmt, AST_RETURN);
                continue;
            }  
            if (i == start_i) {
                printf("Unexpected token '%s' ('%s') in block at line %d or error if error message.\n",tokenTypeToString(tokenList[i].type), tokenList[i].lexeme, tokenList[i].line);
                return NULL;
            }
        }
    }

    ++i;
    
    ASTnode *block = malloc(sizeof(ASTnode));
    if(block==NULL){
        printf("Error malloc in block parser.\n");
        return NULL;
    }
    block->ast_type = AST_BLOCK;
    block->data.block.stmts = stmt_list;
    block->next = NULL;

    *index = i;
    return block;
}