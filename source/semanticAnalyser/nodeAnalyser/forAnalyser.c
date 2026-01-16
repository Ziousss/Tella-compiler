#include "../include/semanticAnalyser/nodeAnalyser.h"

void forAnalyser(ASTnode *forAst, SemContext *context){
    ASTnode *initialisation = forAst->data.for_node.initialisation;
    ASTnode *incrementation = forAst->data.for_node.incrementation;
    ASTnode *condition = forAst->data.for_node.condition;
    ASTnode *block = forAst->data.for_node.block;

    push_scope(context);

    NodeType type = initialisation->ast_type;
    if(type == AST_VAR_DECL){
        char *name = initialisation->data.declaration.identifier;
        SymbolNode *verification = find_in_scope(name, context);
        if(verification != NULL){
            printf("This identifier %s in the for loop line %d is already defined, try finding another name.\n", name, forAst->line);
            context->error_count++;
            return;
        }

        SemanticType type = fromTokToSem(initialisation->data.declaration.type);

        if(type != SEM_INT){
            printf("In the for loop line %d, the initialisation should be of type Int, it is now %s.\n", forAst->line, fromSemToString(type));
            context->error_count++;
            return;
        }

        SymbolNode *sym = malloc(sizeof(SymbolNode));
        sym->kind = SEM_VAR;
        sym->name = strdup(name);
        sym->next = NULL;
        sym->type = type;

        push_variables(sym, context);
    } else {
        printf("This type of AST is not yet supported, please use a declaration as initialization in the for loop line %d.\n", forAst->line);
        context->error_count++;
        return;
    }

    SemanticType condition_type = expressionAnalyser(condition, context);
    if(condition_type != SEM_BOOL){
        printf("The condition of the for loop line %d must result in a boolean. Right now it has type %s.\n", forAst->line, fromSemToString(condition_type));
        context->error_count++;
        pop_scope(context);
        return;
    }

    //could do better because right now 5+2 would be correct.
    SemanticType incrementation_type = expressionAnalyser(incrementation, context);
    if(incrementation_type != SEM_INT){
        printf("The incrementation of the for loop line %d must result in an integer. Right now it has type %s.\n", forAst->line, fromSemToString(incrementation_type));
        context->error_count++;
        pop_scope(context);
        return;      
    }

    blockAnalyser(block, context, false);

    //for the declared variable in the initialization
    pop_scope(context);
    return;
}