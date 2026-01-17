#include "../include/semanticAnalyser/helperFuncAnalyser.h"

void push_scope(SemContext *context){
    ScopeNode *new_scope = malloc(sizeof(ScopeNode));
    new_scope->symbols = NULL;
    new_scope->parent = context->current_scope;
    context->current_scope = new_scope;
}

void pop_scope(SemContext *context){
    ScopeNode *old = context->current_scope;
    context->current_scope = old->parent;
    free(old);
}

void push_variables(SymbolNode *sym, SemContext *context){;
    sym->next = context->current_scope->symbols;
    context->current_scope->symbols = sym;
}

SymbolNode *find_in_scope(char *name, SemContext *context){
    for(ScopeNode *scope = context->current_scope; scope != NULL; scope = scope->parent){
        for(SymbolNode *sym = scope->symbols; sym != NULL; sym = sym->next){
            if(strcmp(sym->name, name) == 0){
                return sym;
            }
        }
    }
    return NULL;
}

//for variablesshadowing
SymbolNode *find_in_current_scope(char *name, SemContext *context){
    for(SymbolNode *sym = context->current_scope->symbols; sym != NULL; sym = sym->next){
        if(strcmp(sym->name, name) == 0){
            return sym;
        }
    }
    return NULL;
}

SemanticType fromTokToSem(Tokentype type){
    switch (type){
        case TOK_CHAR:              return SEM_CHAR;
        case TOK_INT:               return SEM_INT;
        case TOK_TRUE:              return SEM_BOOL;
        case TOK_FALSE:             return SEM_BOOL;
        case TOK_VOID:              return SEM_VOID;
        case TOK_STRING:            return SEM_STRING;
        
        default:                    return SEM_ERROR;
    }
}

char *fromSemToString(SemanticType type){
    switch (type){
        case SEM_INT:       return "Int";
        case SEM_STRING:    return "Char *";
        case SEM_CHAR:      return "Char";
        case SEM_BOOL:      return "Bool";
        case SEM_VOID:      return "Void";
        case SEM_ERROR:     return "Error";

        default:            return "Not named yet";
    }
}

bool isCalculus(Tokentype op){
    return (op == TOK_PLUS || op == TOK_MINUS
        || op == TOK_SLASH || op == TOK_STAR );
}

bool isBool(Tokentype op) {
    return (op == TOK_GREQ || op == TOK_LESS
        || op == TOK_LESSEQ || op == TOK_GR);
}