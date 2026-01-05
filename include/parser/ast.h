#ifndef AST_H
#define AST_H
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "../include/lexer/tokenizer.h"

typedef struct ASTnode ASTnode;

typedef enum {
    AST_PROGRAM,

    AST_FUNC_DEF,
    AST_VAR_DECL,
    AST_PARAM_DECL,

    AST_BLOCK,
    AST_RETURN,
    AST_EXPR_STMT,

    AST_BINARY_EXPR,
    AST_ASSIGN_EXPR,
    AST_CALL_EXPR,

    AST_IDENTIFIER,
    AST_NUMBER,
} NodeType;


typedef struct {
    double value;
} NumberNode;

typedef struct {
    char *name;
} IdentifierNode;

typedef struct {
    ASTnode* indentifier;
    ASTnode* expression;
} AssignementNode; 

typedef struct {
    char operator;
    ASTnode* left;
    ASTnode* right;
} OperatorNode;

typedef struct {
    ASTnode** statements;
    int stmt_count;
} BlockNode;

typedef struct {
    ASTnode** parameters;
    int count;
} ParameterNode;

typedef struct {
    char *name;
    Tokentype return_type;
    ASTnode *parameters;
    ASTnode *body;
} FunctionDefNode;

typedef struct {
    char *name;
    ASTnode** arguments;
    int arg_count;
} FunctionCallNode;

// Main AST node
struct ASTnode {
    NodeType type;
    union {
        NumberNode number;
        OperatorNode operator;
        FunctionDefNode function_def;
        FunctionCallNode function_call;
        BlockNode block;
        IdentifierNode identifier;
        ParameterNode parameter;
        AssignementNode assignement;
    } data;
};

#endif