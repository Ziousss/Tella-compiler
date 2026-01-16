#ifndef STRUCT_H
#define STRUCT_H

typedef struct SymbolNode SymbolNode;
typedef struct ScopeNode ScopeNode;
typedef struct SemContext SemContext;

typedef enum {
    SEM_INT, SEM_CHAR, SEM_STRING, SEM_VOID, SEM_BOOL, SEM_ERROR
} SemanticType;

typedef enum {
    SEM_FCT, SEM_PARAM, SEM_VAR
} SemanticKind;

typedef struct SymbolNode {
    SemanticType type;
    SemanticKind kind;
    char *name;

    int param_count;
    SemanticType *param;

    SymbolNode *next;
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
} SemContext;

#endif