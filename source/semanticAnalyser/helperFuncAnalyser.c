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
    SymbolNode *sym = old->symbols;
    while(sym != NULL){
        SymbolNode *next = sym->next;
        free(sym->name);
        free(sym);
        sym = next;
    }
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

GlobalFunc *getAllFunctions(const SemContext *context) {
    if (!context || !context->current_scope) {
        return NULL;
    }

    SymbolNode *sym = context->current_scope->symbols;
    GlobalFunc *head = NULL;
    GlobalFunc *tail = NULL;

    while (sym) {
        if (sym->kind == SEM_FCT) {
            GlobalFunc *node = malloc(sizeof(GlobalFunc));
            if (!node) {
                printf("Malloc error in getAllFunctions\n");
                return NULL;
            }

            node->name = sym->name;          
            node->type = sym->type;
            node->param_count = sym->param_count;
            node->param = sym->param;        
            node->next = NULL;

            if (!head) {
                head = tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
        }
        sym = sym->next;
    }

    return head;
}


SemanticType fromTokToSem(Tokentype type){
    switch (type){
        case TOK_CHAR:              return SEM_CHAR;
        case TOK_INT:               return SEM_INT;
        case TOK_TRUE:
        case TOK_FALSE:
        case TOK_BOOL:              return SEM_BOOL;
        case TOK_VOID:              return SEM_VOID;
        case TOK_STRING:            return SEM_STRING;
        
        default:                    return SEM_ERROR;
    }
}

const char *fromSemToString(SemanticType type){
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

Tokentype fromSemToTok(SemanticType type){
    switch (type){
        case SEM_CHAR:          return TOK_CHAR;
        case SEM_INT:           return TOK_INT;
        case SEM_BOOL:          return TOK_BOOL;
        case SEM_VOID:          return TOK_VOID;
        case SEM_STRING:        return TOK_STRING;
        
        default:                return TOK_ERROR;
    }
}

//size and typeSize are only for arrays for now
IRsymbole *newIRsym(char *name, SemanticType type, int size){
    IRsymbole *sym = malloc(sizeof(IRsymbole));
    if(sym == NULL){
        printf("Malloc failed for IRsymbole.\n");
        return NULL;
    }

    sym->name = strdup(name);
    sym->type = type;
    sym->size = size;
    sym->next = NULL;
    
    return sym;
}

void pushIRSym(IRsymbole *symIR, SemContext *context){
    if(context->IRsym == NULL){
        context->IRsym = symIR; 
        return;
    }
    SemContext *cur = context;
    while (cur->IRsym->next != NULL){
        cur->IRsym = cur->IRsym->next;
    }
    cur->IRsym->next = symIR;
}