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
        freeASTNode(sym->size);
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

            node->name = strdup(sym->name);          
            node->type = sym->type;
            node->param_count = sym->param_count;
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
        case TOK_SIZET:             return SEM_SIZET;
        
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
        case SEM_ARR_TYPE:  return "Array pointer";
        case SEM_SIZET:     return "Size_t";

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
        case SEM_SIZET:         return TOK_SIZET;
        
        default:                return TOK_ERROR;
    }
}

//size and typeSize are only for arrays for now
IRsymbole *newIRsym(char *name, SemanticType type, int size, char *stringLit, SemanticKind kind){
    IRsymbole *sym = malloc(sizeof(IRsymbole));
    if(sym == NULL){
        printf("Malloc failed for IRsymbole.\n");
        return NULL;
    }

    sym->name = strdup(name);
    sym->type = type;
    sym->size = size;
    sym->next = NULL;
    sym->string_literals = stringLit;
    sym->kind = kind;
    
    return sym;
}

void pushIRSym(IRsymbole *symIR, SemContext *context){
    if(context->IRsym == NULL){
        context->IRsym = symIR; 
        context->IRsym_tail = symIR;
        return;
    }

    context->IRsym_tail->next = symIR;
    context->IRsym_tail = symIR;
}

int compSizeTInt(SemanticType type1, SemanticType type2){
    if(type1 == type2){
        return 0;
    }

    if((type1 == SEM_INT && type2 == SEM_SIZET) || (type1 == SEM_SIZET && type2 == SEM_INT)){
        return 1;
    }

    return 2;
}

bool canConvert(SemanticType target, SemanticType source, ASTnode *expr){
    if(target == source) return true;
    
    if(compSizeTInt(target, source) == 1){
        if(target == SEM_SIZET && source == SEM_INT && expr != NULL){
            if(expr->ast_type == AST_NUMBER && expr->data.int_literal.value < 0){
                return false;
            }
        } 
        return true;
    }

    if(target == SEM_INT && source == SEM_SIZET) return true;
    
    return false;
}

SymbolParams *getParams(ParameterNode *ASTparams){
    ParameterNode *tmp = ASTparams;
    SymbolParams *head = NULL;
    SymbolParams *tail = NULL;

    if(ASTparams == NULL){
        return NULL;
    }

    int count = 0;
    while (tmp != NULL){
        SymbolParams *symParam = malloc(sizeof(SymbolParams));
        if(symParam == NULL){
            for(int i = 0; i < count; i++){
                SymbolParams *next = head->next;
                free(head->name);
                free(head);
                head = next; 
            }
            printf("Malloc failed in getParams\n");
            return NULL;
        }
        count++;

        symParam->name = strdup(tmp->name);
        symParam->type = fromTokToSem(tmp->ret_type);
        symParam->next = NULL;
        symParam->count = count;

        if(head == NULL){
            head = symParam;
            tail = symParam;
        } else {
            tail->next = symParam;
            tail = symParam;
        }

        tmp = tmp->next;
    }
    
    return head;
}

ASTnode *copyAST(ASTnode *node){
    if(node == NULL) return NULL;

    ASTnode *copy = malloc(sizeof(ASTnode));
    if(copy == NULL){
        printf("Malloc failed in copyAST\n");
        return NULL;
    }

    copy->ast_type = node->ast_type;
    copy->line = node->line;
    copy->fileName = node->fileName ? strdup(node->fileName) : NULL;

    switch(node->ast_type){
        case AST_IDENTIFIER:
            copy->data.identifier.name = strdup(node->data.identifier.name);
            break;

        case AST_NUMBER:
            copy->data.int_literal.value = node->data.int_literal.value;
            break;

        case AST_SIZET:
            copy->data.sizeT_literal.value = node->data.sizeT_literal.value;
            break;

        case AST_CHAR_LITERAL:
            copy->data.character_literal.character = node->data.character_literal.character;
            break;

        case AST_BOOLEAN:
            copy->data.boolean_literal.boolean = node->data.boolean_literal.boolean;
            break;

        case AST_STRING_LITERAL:
            copy->data.string_literal.string = strdup(node->data.string_literal.string);
            break;

        case AST_BINARY_EXPR:
            copy->data.binary.op = node->data.binary.op;
            copy->data.binary.left = copyAST(node->data.binary.left);
            copy->data.binary.right = copyAST(node->data.binary.right);
            break;

        case AST_ASSIGN_EXPR:
            copy->data.assign.target = strdup(node->data.assign.target);
            copy->data.assign.value = copyAST(node->data.assign.value);
            break;

        case AST_VAR_DECL:
            copy->data.declaration.type = node->data.declaration.type;
            copy->data.declaration.identifier = strdup(node->data.declaration.identifier);
            copy->data.declaration.expression = copyAST(node->data.declaration.expression);
            break;

        case AST_ARRAY_DECL:
            copy->data.arrayDecl.name = strdup(node->data.arrayDecl.name);
            copy->data.arrayDecl.type = node->data.arrayDecl.type;
            copy->data.arrayDecl.size = copyAST(node->data.arrayDecl.size);
            copy->data.arrayDecl.value = copyAST(node->data.arrayDecl.value);
            break;

        case AST_ASSIGN_ARRAY:
            copy->data.arrayAssign.name = strdup(node->data.arrayAssign.name);
            copy->data.arrayAssign.type = node->data.arrayAssign.type;
            copy->data.arrayAssign.index = copyAST(node->data.arrayAssign.index);
            copy->data.arrayAssign.value = copyAST(node->data.arrayAssign.value);
            break;

        case AST_ARRAY_LOAD:
            copy->data.arrayLoad.name = strdup(node->data.arrayLoad.name);
            copy->data.arrayLoad.index = copyAST(node->data.arrayLoad.index);
            break;

        case AST_FUNC_CALL: {
            copy->data.func_call.name = strdup(node->data.func_call.name);

            ArgNode *src = node->data.func_call.args;
            ArgNode *head = NULL;
            ArgNode *tail = NULL;

            while(src){
                ArgNode *newArg = malloc(sizeof(ArgNode));
                newArg->expression = copyAST(src->expression);
                newArg->next = NULL;

                if(!head) head = tail = newArg;
                else {
                    tail->next = newArg;
                    tail = newArg;
                }
                src = src->next;
            }

            copy->data.func_call.args = head;
            break;
        }

        case AST_BLOCK:
            copy->data.block.stmts = copyAST(node->data.block.stmts);
            break;

        case AST_RETURN:
            copy->data.return_node.expr = copyAST(node->data.return_node.expr);
            break;

        case AST_IF_STMT:
            copy->data.if_node.condition = copyAST(node->data.if_node.condition);
            copy->data.if_node.if_branch = copyAST(node->data.if_node.if_branch);
            copy->data.if_node.else_branch = copyAST(node->data.if_node.else_branch);
            break;

        case AST_WHILE_STMT:
            copy->data.while_node.condition = copyAST(node->data.while_node.condition);
            copy->data.while_node.block = copyAST(node->data.while_node.block);
            break;

        case AST_FOR_STMT:
            copy->data.for_node.initialisation = copyAST(node->data.for_node.initialisation);
            copy->data.for_node.condition = copyAST(node->data.for_node.condition);
            copy->data.for_node.incrementation = copyAST(node->data.for_node.incrementation);
            copy->data.for_node.block = copyAST(node->data.for_node.block);
            break;

        case AST_FUNC_DEF:
        case AST_FUNC_DEF_MAIN:
        case AST_FUNC_SIGN: {
            copy->data.func_def.name = strdup(node->data.func_def.name);
            copy->data.func_def.return_type = node->data.func_def.return_type;
            copy->data.func_def.body = copyAST(node->data.func_def.body);
            copy->data.func_def.param = node->data.func_def.param;

            // copy parameters
            ParameterNode *src = node->data.func_def.parameters;
            ParameterNode *head = NULL;
            ParameterNode *tail = NULL;

            while(src){
                ParameterNode *p = malloc(sizeof(ParameterNode));
                p->name = strdup(src->name);
                p->ret_type = src->ret_type;
                p->count = src->count;
                p->next = NULL;

                if(!head) head = tail = p;
                else {
                    tail->next = p;
                    tail = p;
                }

                src = src->next;
            }

            copy->data.func_def.parameters = head;
            break;
        }

        case AST_PROGRAM:
            copy->data.program_node.func_def = copyAST(node->data.program_node.func_def);
            copy->data.program_node.include = copyAST(node->data.program_node.include);
            break;

        case AST_INCLUDE:
            copy->data.include_node.name = strdup(node->data.include_node.name);
            break;

        default:
            printf("copyAST: unhandled type %d\n", node->ast_type);
            break;
    }

    copy->next = copyAST(node->next);
    return copy;
}