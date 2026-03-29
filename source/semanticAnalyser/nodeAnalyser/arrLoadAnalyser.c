#include "../include/semanticAnalyser/nodeAnalyser.h"

SemanticType arrLoadAnalyser(ASTnode *arrayLoad, SemContext *context){
    char *name = arrayLoad->data.arrayLoad.name;
    SymbolNode *sym = find_in_scope(name, context);
    if(sym == NULL){
        printf("Array \"%s\" line %d was not defined before.\n", name, arrayLoad->line);
        context->error_count++;
        return SEM_ERROR;
    }

    if(arrayLoad->data.arrayLoad.index->ast_type == AST_NUMBER){
        int value = (int)arrayLoad->data.arrayLoad.index->data.int_literal.value;
        if(value < 0){
            printf("Trying to acces a negative index for array \"%s\" line %d.\n", name, arrayLoad->line);
            context->error_count++;
            return SEM_ERROR;
        }
        if(sym->size->ast_type == AST_NUMBER){
            if((int)sym->size->data.int_literal.value <= value){
                printf("Trying to acces an out of bound index for array \"%s\" line %d.\n", name, arrayLoad->line);
                context->error_count++;
                return SEM_ERROR;
            }
        }
    }

    if(sym->type == SEM_STRING){
        return SEM_CHAR;
    }

    return sym->type;
}