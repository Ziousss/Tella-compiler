#ifndef STRUCT_H
#define STRUCT_H

#include "../include/parser/ast.h"

typedef struct SymbolNode SymbolNode;
typedef struct ScopeNode ScopeNode;
typedef struct SemContext SemContext;
typedef struct GlobalFunc GlobalFunc;
typedef struct IRsymbole IRsymbole;

typedef enum {
    SEM_INT, SEM_CHAR, SEM_STRING, SEM_VOID, SEM_BOOL, SEM_ERROR, SEM_ARR_TYPE, SEM_SIZET
} SemanticType;

typedef enum {
    SEM_FCT, SEM_PARAM, SEM_VAR, SEM_ARR
} SemanticKind;

typedef struct SymbolNode {
    SemanticType type;
    SemanticKind kind;
    char *name;

    //for array
    ASTnode *size;
    bool isArr;
    char *stringLiteral;

    int param_count;
    SemanticType *param;

    SymbolNode *next;
    int line;
} SymbolNode;

typedef struct ScopeNode {
    ScopeNode *parent;
    SymbolNode *symbols;
} ScopeNode;

typedef struct SemContext {
    ScopeNode *current_scope;
    SymbolNode *current_function;
    bool saw_return;
    int error_count;

    IRsymbole *IRsym;
    IRsymbole *IRsym_tail;
} SemContext;

//For now has issue with several variables having same name in different functions
//Idea to solve, also link the name of the func.
typedef struct IRsymbole{
    char *name;
    SemanticType type;

    //For arrays
    int size;
    char *string_literals;

    //Linked list
    IRsymbole *next;
} IRsymbole;


typedef struct GlobalFunc {
    SemanticType type;
    char *name;
    int param_count;
    SemanticType *param;

    IRsymbole *sym;
    GlobalFunc *next;
} GlobalFunc;

#endif