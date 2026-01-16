#include "../include/semanticAnalyser/helperFuncAnalyser.h"

static SymbolNode *stack_scope = NULL;

void push_to_scope(SymbolNode *sym){
    sym->next = stack_scope;
    stack_scope = sym;
}

void pop_out_scope(int count){
    while(stack_scope != NULL && count-- > 0){
        SymbolNode *tmp = stack_scope;
        stack_scope = stack_scope->next;
        free(tmp->name);
        free(tmp);
    }
}

SymbolNode *find_in_scope(char *name){
    SymbolNode *cur = stack_scope;
    while(cur){
        if(strcmp(cur->name, name) == 0){
            return cur;
        }

        cur = cur->next;
    }
    return NULL;
}

SemanticType fromTokToSem(Tokentype type){
    switch (type){
        case TOK_CHAR:              return SEM_CHAR;
        case TOK_STRING_LITERAL:    return SEM_STRING;
        case TOK_INT:               return SEM_INT;
        case TOK_VOID:              return SEM_VOID;
        
        default:                    return SEM_ERROR;
    }
}

char *fromSemToString(SemanticType type){
    switch (type){
        case SEM_INT:       return "Int";
        case SEM_CHAR:      return "Char";
        case SEM_STRING:    return "String";
        case SEM_VOID:      return "Void";

        default:            return "Not name yet";
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