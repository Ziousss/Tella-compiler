#ifndef AST_H
#define AST_H
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "../include/lexer/tokenizer.h"

typedef struct ASTnode ASTnode;
typedef struct ParameterNode ParameterNode;
typedef struct ArgNode ArgNode;

typedef enum {
    AST_PROGRAM,

    AST_FUNC_DEF,
    AST_FUNC_CALL,
    AST_VAR_DECL,
    AST_PARAM_DECL,
    AST_PARAM_LIST,

    AST_BLOCK,
    AST_STMT_LIST,
    AST_RETURN,
    AST_EXPR_STMT,
    AST_IF_STMT,
    AST_FOR_STMT,
    AST_WHILE_STMT,

    AST_BINARY_EXPR,
    AST_ASSIGN_EXPR,
    AST_CALL_EXPR,

    AST_IDENTIFIER,
    AST_NUMBER,
} NodeType;

typedef struct ParameterNode {
    Tokentype ret_type;
    int count;
    char *name;
    ParameterNode *next;
} ParameterNode;

typedef struct ArgNode {
    ASTnode *expression;
    ArgNode *next;
} ArgNode;

typedef struct ASTnode {
    NodeType ast_type;
    union {
        struct { 
            char *name; 
        } identifier;

        struct { 
            int value; 
        } int_literal;
        
        struct { 
            Tokentype op; 
            ASTnode *left; 
            ASTnode *right; 
        } binary;
        
        struct { 
            char *name; 
            ArgNode *args; 
        } func_call;
        
        struct { 
            ASTnode *target; 
            ASTnode *value; 
        } assign;

        struct {
            Tokentype type;
            char *identifier;
            ASTnode *expression;
        } declaration;
        
        struct { 
            ASTnode *stmts; 
        } block;
        
        struct { 
            ASTnode *expr; 
        } return_node;

        struct {
            ASTnode *condition;
            ASTnode *if_branch;
            ASTnode *else_branch;
        } if_node;
        
        struct { 
            char *name; 
            Tokentype return_type; 
            ParameterNode *parameters; 
            ASTnode *body; 
        } func_def;
    } data;

    struct ASTnode *next; 
} ASTnode;


#endif