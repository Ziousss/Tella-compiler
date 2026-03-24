#include "../include/semanticAnalyser/nodeAnalyser.h"

void arrayAssignAnalyser(ASTnode *arrayAssign, SemContext *context){
    SymbolNode *target = find_in_scope(arrayAssign->data.arrayAssign.name, context);
    if(target == NULL){
        printf("Identifier \"%s\" on the left side of the assignment line %d is not defined yet.\n", arrayAssign->data.arrayAssign.name, arrayAssign->line);
        context->error_count++;
        return;
    }
    if(target->kind != SEM_ARR){
        printf("Left side of assignment at line %d is not an assignable array.\n", arrayAssign->line);
        context->error_count++;
        return;
    }
    if(target->size == NULL){
        printf("Internal error: array \"%s\" has no size.\n", target->name);
        context->error_count++;
        return;
    }
    if(target->size->ast_type == AST_NUMBER && arrayAssign->data.arrayAssign.index->ast_type == AST_NUMBER){
        int size = target->size->data.int_literal.value;
        int index = arrayAssign->data.arrayAssign.index->data.int_literal.value;
        
        if(index < 0){
            printf("Index of the array assignment line %d is negative (%d).\n", arrayAssign->line, arrayAssign->data.arrayAssign.index->data.int_literal.value);
            context->error_count++;
        } 
        if(index >= size){
            printf("Index of the array assignment line %d is greater than the maximum size of the declared array (%d).\n", arrayAssign->line, target->size->data.int_literal.value);
            context->error_count++;
        }
    } else {
        SemanticType sizeType = expressionAnalyser(target->size, context);
        SemanticType indexType = expressionAnalyser(arrayAssign->data.arrayAssign.index, context);

        if(sizeType != SEM_INT){
            printf("The declared size of the array \"%s\" is not an integer line %d.\n", target->name, target->line);
            context->error_count++;
        } 
        if(indexType != SEM_INT){
            printf("The index of the array \"%s\" line %d is not an integer.\n", arrayAssign->data.arrayAssign.name, arrayAssign->line);
            context->error_count++;
        }
    }

    SemanticType target_type = target->type;
    SemanticType value_type = expressionAnalyser(arrayAssign->data.arrayAssign.value,context);
    if(value_type == SEM_ERROR){
        return;
    }

    if(target_type != value_type){
        printf("Type missmatch on assignement line %d. The left is type %s and right is type %s.\n", arrayAssign->line, fromSemToString(target_type), fromSemToString(value_type));
        context->error_count++;
        return;
    }

    arrayAssign->data.arrayAssign.type = fromSemToTok(target_type);
}