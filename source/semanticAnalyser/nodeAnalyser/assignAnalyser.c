#include "../include/semanticAnalyser/nodeAnalyser.h"

void assignAnalyser(ASTnode *assignment, SemContext *context){
    SymbolNode *target = find_in_scope(assignment->data.assign.target, context);
    if(target == NULL){
        printf("Identifier %s on the left side of the assignment line %d is not defined yet.\n", assignment->data.assign.target, assignment->line);
        context->error_count += 1;
        return;
    }

    SemanticType target_type = target->type;
    SemanticType value_type = expressionAnalyser(assignment->data.assign.value,context);

    if(value_type == SEM_ERROR){
        return;
    }

    if(target_type != value_type){
        printf("Type missmatch on assignement line %d. The left is type %s and right is type %s", assignment->line, fromSemToString(target_type), fromSemToString(value_type));
        context->error_count += 1;
        return;
    }
}