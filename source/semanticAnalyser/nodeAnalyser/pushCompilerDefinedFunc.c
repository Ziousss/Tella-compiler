#include "../include/semanticAnalyser/nodeAnalyser.h"

void pushCompilerDefinedFunc(char *funcName, SemContext *context, size_t line){
    if(strcmp(funcName, "tellaPutChar") == 0){
        SymbolNode *sym = malloc(sizeof(SymbolNode));
        if(sym == NULL){
            printf("Malloc failed in pushCompilerDefinedFunc for tellaPutChar.\n");
            context->error_count++;
            return;
        }

        sym->name = strdup(funcName);
        sym->kind = SEM_FCT;
        sym->size = NULL;
        sym->stringLiteral = NULL;
        sym->next = NULL;
        sym->param_count = 1;
        
        SymbolParams *param = malloc(sizeof(SymbolParams));
        if(param == NULL){
            printf("Malloc failed for params in pushCompilerDefinedFunc for tellaPurChar.\n");
            context->error_count++;
            return;
        }
        param->next = NULL;
        param->type = SEM_CHAR;
        //Name not checked for funcCalls anyway
        param->name = NULL;
        param->count = 1;

        sym->param = param;
        sym->isArr = false;
        sym->line = line;

        push_variables(sym, context);
    }
    else if(strcmp(funcName, "tellaPrint") == 0){
        SymbolNode *sym = malloc(sizeof(SymbolNode));
        if(sym == NULL){
            printf("Malloc failed in pushCompilerDefinedFunc for tellPrint.\n");
            context->error_count++;
            return;
        }

        sym->name = strdup(funcName);
        sym->kind = SEM_FCT;
        sym->size = NULL;
        sym->stringLiteral = NULL;
        sym->next = NULL;
        sym->param_count = 1;
        
        SymbolParams *param = malloc(sizeof(SymbolParams));
        if(param == NULL){
            printf("Malloc failed for params in pushCompilerDefinedFunc for tellPrint.\n");
            context->error_count++;
            return;
        }
        param->next = NULL;
        param->type = SEM_STRING;
        //Name not checked for funcCalls anyway
        param->name = NULL;
        param->count = 1;

        sym->param = param;
        sym->isArr = false;
        sym->line = line;

        push_variables(sym, context);
    }
}