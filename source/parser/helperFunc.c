#include "../include/parser/helperFunc.h"

bool isTOKType(Tokentype type){
    return (type == TOK_INT || type == TOK_VOID || type == TOK_CHAR 
            || type == TOK_STRING || type == TOK_TRUE || type == TOK_FALSE 
            || type == TOK_BOOL   || type == TOK_SIZET);
}

bool isOperatorExpression (Tokentype type) {
    return (type == TOK_PLUS || type == TOK_MINUS || type == TOK_STAR 
        || type == TOK_SLASH || type == TOK_EQEQ || type == TOK_PLUSEQ
        || type == TOK_MINUSEQ || type == TOK_UNEQ || type == TOK_LESS
        || type == TOK_LESSEQ || type == TOK_GR || type == TOK_GREQ
        || type == TOK_OR || type == TOK_AND);
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

void add_stmt_list(ASTnode **head, ASTnode **last, ASTnode *stmt, NodeType ast_type) {
    stmt->ast_type = ast_type;
    stmt->next = NULL;

    if (*head == NULL){
        *head = stmt;
        *last = stmt;
    } else {
        (*last)->next = stmt;
        *last = stmt;
    }
}

void prinast(ASTnode *node){
    if(node == NULL){
        printf("programAST is NULL.\n");
        return;
    }
    printf("programAST is not NULL.\n");
}

const char* astTypeToString(NodeType type) {
    switch (type) {
        case AST_PROGRAM:           return "PROGRAM_AST";
        case AST_VAR_DECL:          return "DECLARATION_AST";
        case AST_ASSIGN_EXPR:       return "ASSIGN_AST";
        case AST_BINARY_EXPR:       return "BINARY_AST";
        case AST_BLOCK:             return "BLOCK_AST";
        case AST_FOR_STMT:          return "FOR_STMT_AST";
        case AST_WHILE_STMT:        return "WHILE_STMT_AST";
        case AST_IF_STMT:           return "IF_STMT_AST";
        case AST_INCLUDE:           return "INCLUDE_AST";
        case AST_RETURN:            return "RETURN_AST";
        case AST_ARRAY_DECL:        return "ARRAY_DECL_AST";
        case AST_ASSIGN_ARRAY:      return "ARRAY_ASSIGN_AST";
        case AST_ARRAY_LOAD:        return "ARRAY_LOAD_AST";

        case AST_FUNC_CALL:         return "FUNC_CALL_AST";
        case AST_BOOLEAN:           return "BOOL_AST";
        case AST_FUNC_DEF:          return "FUNC_DEF_AST";
        case AST_FUNC_DEF_MAIN:     return "FUNC_DEF_MAIN_AST";
        case AST_FUNC_SIGN:         return "FUNC_SIGNATURE_AST";
        case AST_IDENTIFIER:        return "IDENTIFIER_AST";
        case AST_NUMBER:            return "NUMBER_AST";
        case AST_STRING_LITERAL:    return "STRING_AST";
        case AST_CHAR_LITERAL:      return "CHAR_AST";

        default:{
            static char buffer[64];
            snprintf(buffer, sizeof(buffer), "NOT_NAMED_YET (%d)", type);
            return buffer;
        }
    }
}

Tokentype fromTypeToPTR(Tokentype type){
    switch (type){
        case TOK_CHAR:      return TOK_CHAR_PTR;
        case TOK_INT:       return TOK_INT_PTR;

        default:  return TOK_ERROR;
    }
}

char processChar(const char *string){
    if(strlen(string) == 1){
        return string[0];
    }

    if(strlen(string) >= 2 && string[0] == '\\'){
        switch (string[1]){
            case 'n':           return '\n';
            case 't':           return '\t';
            case 'r':           return '\r';
            case '0':           return '\0';
            case '\\':          return '\\';
            case '\'':          return '\'';
            case '"':           return '\"';
            default:            return string[1];
        }
    }

    printf("Error in processChar.\n");
    return '\0';
}