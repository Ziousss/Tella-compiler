#include "../include/semanticAnalyser/nodeAnalyser.h"

void stmtAnalyser(ASTnode *stmtAst, SemContext *context){
    NodeType astType = stmtAst->ast_type;
    switch (astType){
        case AST_ARRAY_DECL: {
            if(find_in_current_scope(stmtAst->data.arrayDecl.name,context)){
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
                    printf("The size of the array \"%s\" is negative line %ld file %s.\n", stmtAst->data.arrayDecl.name, stmtAst->line, stmtAst->fileName);
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
            sym->size = copyAST(stmtAst->data.arrayDecl.size);
            sym->name = strdup(stmtAst->data.arrayDecl.name);
            sym->type = arrType;
            sym->next = NULL;
            sym->line = stmtAst->line;

            push_variables(sym, context);

            IRsymbole *symIR = newIRsym(stmtAst->data.arrayDecl.name, arrType, size, NULL, SEM_ARR);
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
                        printf("Warning: Declaring an size_t variable %s with a type int object on line %ld file %s.\n", stmtAst->data.declaration.identifier,stmtAst->line, stmtAst->fileName);
                    }
                    if(stmtAst->data.declaration.expression->ast_type == AST_NUMBER && stmtAst->data.declaration.expression->data.int_literal.value < 0){
                        context->error_count++;
                        return;
                    }
                } else if(right_type != left_type){
                    printf("On declaration line %ld in file %s, the right side has %s type but the left is defined as %s type.\n", stmtAst->line, stmtAst->fileName, fromSemToString(right_type), fromSemToString(left_type));
                    context->error_count++;
                    return;
                }                
            }

            SymbolNode *sym = malloc(sizeof(SymbolNode));
            if(sym == NULL){
                printf("Malloc failed for sym in AST_VAR_DECL.\n");
                context->error_count++;
                return;
            }
            sym->kind = SEM_VAR;
            sym->size = NULL;
            sym->name = strdup(stmtAst->data.declaration.identifier);
            sym->type = left_type;
            int size = -1;

            char *stringLit = NULL;
            if(left_type == SEM_STRING){
                ASTnode *sizeAST = malloc(sizeof(ASTnode));
                if(sizeAST == NULL){
                    printf("Malloc failed for size in stmtAnalyser.\n");
                    context->error_count++;
                    return;
                }

                if(stmtAst->data.declaration.expression != NULL && stmtAst->data.declaration.expression->ast_type == AST_STRING_LITERAL){
                    stringLit = stmtAst->data.declaration.expression->data.string_literal.string;

                    sizeAST->ast_type = AST_NUMBER;
                    sizeAST->next = NULL;
                    sizeAST->data.int_literal.value = (int)strlen(stringLit);
                    sizeAST->line = stmtAst->line;
                    sizeAST->fileName = strdup(stmtAst->fileName);

                    sym->size = sizeAST;
                    size = (int)strlen(stringLit);
                    sym->stringLiteral = stringLit;
                } else {
                    sizeAST->ast_type = AST_NUMBER;
                    sizeAST->next = NULL;
                    sizeAST->data.int_literal.value = -2;
                    sizeAST->line = stmtAst->line;

                    sym->size = sizeAST;
                    sym->stringLiteral = NULL;
                }
            } else {
                sym->size = NULL;
            }
            
            sym->next = NULL;

            push_variables(sym, context);

            IRsymbole *symIR = newIRsym(stmtAst->data.declaration.identifier, left_type, size, stringLit, SEM_VAR);
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
        case AST_FOR_STMT:{
            forAnalyser(stmtAst, context);
            break;
        }
        case AST_FUNC_CALL:{
            funcCallAnalyser(stmtAst, context);
            break;
        }

        default: {
            break;
        }
    }
}