#include "../include/IntermediateRep/IRheader.h"

IRstruct *programIR(ASTnode *program, GlobalFunc *definedFunc){
    if(program->ast_type != AST_PROGRAM){
        printf("Given AST is not the program AST.\n");
        return NULL;
    }

    IRContext *context = malloc(sizeof(IRContext));
    if(context == NULL){
        printf("Malloc error in programIR.\n");
        return NULL;
    }

    context->head = NULL;
    context->tail = NULL;
    context->current_label = 0;
    context->current_tmp = 0;
    context->errors = 0;
    context->IRsym = definedFunc->sym;

    initGlobalFunctions(definedFunc);
    ASTnode *funcdef = program->data.program_node.func_def;
    while(funcdef != NULL){
        if(funcdef->ast_type == AST_FUNC_DEF || funcdef->ast_type == AST_FUNC_DEF_MAIN){
            funcDefIR(funcdef, context);
        }
        funcdef = funcdef->next;
    }

    if(context->errors == 0){
        IRstruct *head = context->head;
        
        IRsymbole *sym = context->IRsym;
        while(sym != NULL){
            IRsymbole* next = sym->next;
            free(sym->name);
            free(sym);
            sym = next;
        }
        free(context);
        return head;
    }

    printf("Failed somewhere, %d errors.\n", context->errors);
    free(context);
    return NULL;    
}