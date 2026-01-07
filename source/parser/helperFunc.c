#include "../include/parser/helperFunc.h"

bool isTOKType(Tokentype type){
    if(type != TOK_INT && type != TOK_CHAR && type != TOK_VOID){
        return false;
    }
    return true;
}

ParameterNode *create_param_tree(char *name, Tokentype type, int count){
    ParameterNode *tmp = malloc(sizeof(ParameterNode));
    tmp->next = NULL;
    tmp->count = count;
    tmp->name = name;
    tmp->ret_type = type;
    return tmp;
}

void param_list_add(ParameterNode **head, ParameterNode *param) {
    if(*head == NULL){
        *head = param;
        return;
    }

    ParameterNode *cur = *head;
    while(cur->next){
        cur = cur->next;
    }
    cur->next = param;
}

void add_stmt_list(ASTnode *head, ASTnode *last, ASTnode *stmt, Tokentype ast_type) {
    if (head == NULL){
        head = stmt;
        head->ast_type = ast_type;
    } else {
        last->next = stmt;
        last->next->ast_type = ast_type;
    }

    last = stmt;
}