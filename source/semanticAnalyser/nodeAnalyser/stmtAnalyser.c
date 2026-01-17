#include "../include/semanticAnalyser/nodeAnalyser.h"

void stmtAnalyser(ASTnode *stmtAst, SemContext *context){
    NodeType ast_type = stmtAst->ast_type;
    switch (ast_type){
        case AST_VAR_DECL: {
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
                if(right_type != left_type){
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
            break;
        }
        case AST_RETURN: {
            returnAnalyser(stmtAst, context);
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
    }
}