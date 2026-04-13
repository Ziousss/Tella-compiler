#include "../include/semanticAnalyser/nodeAnalyser.h"

void forAnalyser(ASTnode *forAst, SemContext *context){
    ASTnode *initialisation = forAst->data.for_node.initialisation;
    ASTnode *incrementation = forAst->data.for_node.incrementation;
    ASTnode *condition = forAst->data.for_node.condition;
    ASTnode *block = forAst->data.for_node.block;

    push_scope(context);

    NodeType nodeType = initialisation->ast_type;
    if(nodeType == AST_VAR_DECL){
        char *name = initialisation->data.declaration.identifier;
        SymbolNode *verification = find_in_scope(name, context);
        if(verification != NULL){
            printf("This identifier %s in the for loop line %ld file %s is already defined, try finding another name.\n", name, forAst->line, forAst->fileName);
            context->error_count++;
            return;
        }

        SemanticType semType = fromTokToSem(initialisation->data.declaration.type);

        if(semType != SEM_INT){
            printf("In the for loop line %ld file %s, the initialisation should be of type Int, it is now %s.\n", forAst->line, forAst->fileName, fromSemToString(semType));
            context->error_count++;
            return;
        }

        SymbolNode *symNode = malloc(sizeof(SymbolNode));
        if(symNode == NULL){
            printf("Malloc failed for symNode in forAnalyser.\n");
            context->error_count++;
            return;
        }

        symNode->kind = SEM_VAR;
        symNode->size = NULL;
        symNode->name = strdup(name);
        symNode->next = NULL;
        symNode->type = semType;

        push_variables(symNode, context);

        IRsymbole *symIR = newIRsym(name, semType, -1, NULL, SEM_VAR);
        if(symIR == NULL){
            return;
        }

        pushIRSym(symIR, context);
    } else {
        printf("This type of AST is not yet supported, please use a declaration as initialization in the for loop line %ld file %s.\n", forAst->line, forAst->fileName);
        context->error_count++;
        return;
    }

    SemanticType condition_type = expressionAnalyser(condition, context);
    if(condition_type != SEM_BOOL){
        printf("The condition of the for loop line %ld file %s must result in a boolean. Right now it has type %s.\n", forAst->line, forAst->fileName, fromSemToString(condition_type));
        context->error_count++;
        pop_scope(context);
        return;
    }

    //could do better because right now 5+2 would be correct.
    SemanticType incrementation_type = expressionAnalyser(incrementation, context);
    if(incrementation_type != SEM_INT){
        printf("The incrementation of the for loop line %ld file %s must result in an integer. Right now it has type %s.\n", forAst->line, forAst->fileName, fromSemToString(incrementation_type));
        context->error_count++;
        pop_scope(context);
        return;      
    }

    blockAnalyser(block, context, false);

    //for the declared variable in the initialization
    pop_scope(context);
    return;
}