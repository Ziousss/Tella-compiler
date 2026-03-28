#include "../include/semanticAnalyser/nodeAnalyser.h"

void stmtAnalyser(ASTnode *stmtAst, SemContext *context){
    NodeType ast_type = stmtAst->ast_type;
    switch (ast_type){
        case AST_ARRAY_DECL: {
            if(find_in_current_scope(stmtAst->data.arrayDecl.name, context)){
                printf("Redefinition of the %s identifier in the same scope.\n", stmtAst->data.arrayDecl.name);
                context->error_count++;
                return;
            }

            SemanticType arrType = fromTokToSem(stmtAst->data.arrayDecl.type);

            //So now -1 means not an array and -2 means it is an array but with an expression as index.
            int size = -2;
            if(stmtAst->data.arrayDecl.size->ast_type == AST_NUMBER){
                size = stmtAst->data.arrayDecl.size->data.int_literal.value;
                if(size < 0){
                    printf("The size of the array \"%s\" is negative line %d.\n", stmtAst->data.arrayDecl.name, stmtAst->line);
                    context->error_count++;
                    return;
                }
            }

            SymbolNode *sym = malloc(sizeof(SymbolNode));
            if(sym == NULL){
                printf("Malloc failed for sym in AST_ARRAY_DECL.\n");
                return;
            }

            sym->kind = SEM_ARR;
            sym->size = stmtAst->data.arrayDecl.size;
            sym->name = strdup(stmtAst->data.arrayDecl.name);
            sym->type = arrType;
            sym->next = NULL;
            sym->line = stmtAst->line;

            push_variables(sym, context);

            IRsymbole *symIR = newIRsym(stmtAst->data.arrayDecl.name, arrType, size);
            if(symIR == NULL){
                context->error_count++;
                return;
            }
            pushIRSym(symIR, context);

            break;
        }
        case AST_VAR_DECL:{
            if(find_in_current_scope(stmtAst->data.declaration.identifier, context)){
                printf("Redefinition of the %s identifier in the same scope.\n", stmtAst->data.declaration.identifier);
                context->error_count++;
                return;
            }

            SemanticType left_type = fromTokToSem(stmtAst->data.declaration.type);
            if(stmtAst->data.declaration.expression != NULL){
                SemanticType right_type = expressionAnalyser(stmtAst->data.declaration.expression, context);
                if(right_type == SEM_ERROR){
                    return;
                }

                if(left_type == SEM_SIZET && right_type == SEM_INT){
                    if(stmtAst->data.declaration.expression->ast_type != AST_NUMBER || !canConvert(left_type, right_type, stmtAst->data.declaration.expression)){
                        printf("Warning: Declaring an size_t variable %s with a type int object on line %d.\n", stmtAst->data.declaration.identifier,stmtAst->line);
                    }
                    if(stmtAst->data.declaration.expression->ast_type == AST_NUMBER && stmtAst->data.declaration.expression->data.int_literal.value < 0){
                        context->error_count++;
                        return;
                    }
                } else if(right_type != left_type){
                    printf("On declaration line %d, the right side has %s type but the left is defined as %s type.\n", stmtAst->line, fromSemToString(right_type), fromSemToString(left_type));
                    context->error_count++;
                    return;
                }                
            }

            SymbolNode *sym = malloc(sizeof(SymbolNode));
            sym->kind = SEM_VAR;
            sym->name = strdup(stmtAst->data.declaration.identifier);
            sym->type = left_type;
            sym->next = NULL;

            push_variables(sym, context);
            IRsymbole *symIR = newIRsym(stmtAst->data.declaration.identifier, left_type, -1);
            if(symIR == NULL){
                context->error_count++;
                return;
            }
            pushIRSym(symIR, context);
            break;
        }
        case AST_RETURN: {
            returnAnalyser(stmtAst, context);
            break;
        }
        case AST_ASSIGN_ARRAY: {
            arrayAssignAnalyser(stmtAst, context);
            break;
        }
        case AST_ASSIGN_EXPR: {
            assignAnalyser(stmtAst, context);
            break;
        }
        case AST_IF_STMT: {
            ifAnalyser(stmtAst, context);
            break;
        }
        case AST_WHILE_STMT: {
            whileAnalyser(stmtAst, context);
            break;
        }

        default: {
            break;
        }
    }
}