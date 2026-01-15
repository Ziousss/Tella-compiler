#include "../include/semanticAnalyser/nodeAnalyser.h"

void stmtAnalyser(ASTnode *stmtAst, int *count, SemContext *context){
    NodeType ast_type = stmtAst->ast_type;
    switch (ast_type){
        case AST_VAR_DECL: {
            if(find_in_scope(stmtAst->data.declaration.identifier)){
                printf("Redefinition of the %s identifier.\n", stmtAst->data.declaration.identifier);
                return;
            }

            SymbolNode *sym = malloc(sizeof(SymbolNode));
            sym->kind = SEM_VAR;
            sym->name = strdup(stmtAst->data.declaration.identifier);
            sym->type = fromTokToSem(stmtAst->data.declaration.type);
            sym->next = NULL;

            push_to_scope(sym);
            (*count)++;

            if(stmtAst->data.declaration.expression != NULL){
                expressionAnalyser(stmtAst->data.declaration.expression, context);
            }
            break;
        }
        case AST_RETURN: {
            returnAnalyser(stmtAst->data.return_node.expr, context);
            break;
        }
        case AST_ASSIGN_EXPR: {
            assignAnalyser(stmtAst, context);
            break;
        }
        case AST_IF_STMT: {
            SemanticType condition_type = expressionAnalyser(stmtAst->data.if_node.condition, context);
            
            blockAnalyser(stmtAst->data.if_node.if_branch, context);
            if(stmtAst->data.if_node.else_branch, context){
                blockAnalyser(stmtAst->data.if_node.else_branch, context);
            }
            break;
        }
    }
}