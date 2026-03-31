#include "../include/semanticAnalyser/nodeAnalyser.h"

SemanticType assignAnalyser(ASTnode *assignment, SemContext *context){
    SymbolNode *target = find_in_scope(assignment->data.assign.target, context);
    if(target == NULL){
        printf("Identifier %s on the left side of the assignment line %d is not defined yet.\n", assignment->data.assign.target, assignment->line);
        context->error_count++;
        return SEM_ERROR;
    }
    
    if(target->kind != SEM_VAR && target->kind != SEM_PARAM){
        printf("Left side of assignment at line %d is not assignable.\n", assignment->line);
        context->error_count++;
        return SEM_ERROR;
    }
    
    SemanticType target_type = target->type;
    SemanticType value_type = expressionAnalyser(assignment->data.assign.value, context);
    if(value_type == SEM_ERROR){
        return SEM_ERROR;
    }
    
    if(target_type == value_type){
        return target_type;
    }
    
    if(compSizeTInt(target_type, value_type) == 1){
        if(!canConvert(target_type, value_type, assignment->data.assign.value)){
            printf("Invalid assignment on line %d: cannot assign %s to %s\n", assignment->line, fromSemToString(value_type), fromSemToString(target_type));
            context->error_count++;
            return SEM_ERROR;
        }
        
        if(target_type == SEM_SIZET && value_type == SEM_INT){
            if(assignment->data.assign.value->ast_type == AST_NUMBER && assignment->data.assign.value->data.int_literal.value < 0){
                printf("Warning: assigning negative literal to size_t on line %d\n", assignment->line);
            }
        }
        return value_type;
    }
    
    printf("Type mismatch on assignment line %d: %s vs %s\n", assignment->line, fromSemToString(target_type), fromSemToString(value_type));
    context->error_count++;
    return SEM_ERROR;
}