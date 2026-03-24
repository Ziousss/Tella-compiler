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
        int value = arrayLoad->data.arrayLoad.index->data.int_literal.value;
        if(value < 0){
            printf("Trying to acces a negative index for array \"%s\" line %d.\n", name, arrayLoad->line);
            context->error_count++;
            return SEM_ERROR;
        }
    }

    return sym->type;
}