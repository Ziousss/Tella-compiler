#include "../include/parser/helperFunc.h"

bool isTOKType(Tokentype type){
    return (type == TOK_INT || type == TOK_VOID || type == TOK_CHAR || type == TOK_STRING || type == TOK_TRUE || type == TOK_FALSE);
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

        case AST_FUNC_CALL:         return "FUNC_CALL_AST";
        case AST_BOOLEAN:           return "BOOL_AST";
        case AST_FUNC_DEF:          return "FUNC_DEF_AST";
        case AST_FUNC_DEF_MAIN:     return "FUNC_DEF_MAIN_AST";
        case AST_IDENTIFIER:        return "IDENTIFIER_AST";
        case AST_NUMBER:            return "NUMBER_AST";
        case AST_STRING_LITERAL:    return "STRING_AST";

        default:                    return "NOT_NAMED_YET";
    }
}   

void freeASTNode(ASTnode *node){
    if(node == NULL){
        return;
    }

    NodeType type = node->ast_type;
    switch (type) {
        case AST_FUNC_DEF:
        case AST_FUNC_DEF_MAIN: {
            free(node->data.func_def.name);
            freeASTNode(node->data.func_def.body);
            
            ParameterNode *param = node->data.func_def.parameters;
            if(param != NULL) {  // ← AJOUTER CE CHECK!
                ParameterNode *current = param;
                while (current != NULL){
                    ParameterNode *next = current->next;
                    free(current->name);
                    free(current);
                    current = next;
                }
            }
            break;
        }
        case AST_ASSIGN_EXPR: {
            freeASTNode(node->data.assign.value);
            free(node->data.assign.target);
            break;
        }
        case AST_BINARY_EXPR:{
            freeASTNode(node->data.binary.left);
            freeASTNode(node->data.binary.right);
            break;
        }
        case AST_BLOCK: {
            freeASTNode(node->data.block.stmts);
            break;
        }
        case AST_BOOLEAN: 
        case AST_NUMBER:
        case AST_CHAR_LITERAL:{
            break;
        }
        case AST_FOR_STMT:{
            freeASTNode(node->data.for_node.block);
            freeASTNode(node->data.for_node.condition);
            freeASTNode(node->data.for_node.incrementation);
            freeASTNode(node->data.for_node.initialisation);
            break;
        }
        case AST_FUNC_CALL:{
            free(node->data.func_call.name);
            ArgNode *arg = node->data.func_call.args;
            ArgNode *current = arg;
            while(current != NULL){
                ArgNode *next = current->next;
                freeASTNode(current->expression);
                free(current);
                current = next;
            } 
            break;
        }
        case AST_IDENTIFIER:{
            free(node->data.identifier.name);
            break;
        }
        case AST_IF_STMT:{
            freeASTNode(node->data.if_node.condition);
            freeASTNode(node->data.if_node.else_branch);
            freeASTNode(node->data.if_node.if_branch);
            break;
        }
        
        case AST_RETURN:{
            freeASTNode(node->data.return_node.expr);
            break;
        }
        case AST_VAR_DECL:{
            free(node->data.declaration.identifier);
            freeASTNode(node->data.declaration.expression);
            break;
        }
        case AST_STRING_LITERAL:{
            free(node->data.string_literal.string);
            break;
        }
        case AST_WHILE_STMT:{
            freeASTNode(node->data.while_node.condition);
            freeASTNode(node->data.while_node.block);
            break;
        }
        default:{
            printf("Unknown ast type.");
            break;
        }
    }

    if(node->next != NULL) {
        freeASTNode(node->next);
    }

    free(node);
}