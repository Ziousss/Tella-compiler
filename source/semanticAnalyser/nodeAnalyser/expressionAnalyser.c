#include "../include/semanticAnalyser/nodeAnalyser.h"

SemanticType expressionAnalyser(ASTnode *expressionAst, SemContext *context){
    Tokentype type = expressionAst->ast_type;
    switch (type){
        case AST_IDENTIFIER: {
            SymbolNode *identifier =  find_in_scope(expressionAst->data.identifier.name, context);
            if (identifier == NULL){
                printf("Identifier %s line %d not defined yet.\n", expressionAst->data.identifier.name, expressionAst->line);
                context->error_count += 1;
                return SEM_ERROR;
            }
            SemanticType identifier_type = identifier->type;
            return identifier_type;
        }

        case AST_NUMBER:            return SEM_INT;
        case AST_STRING_LITERAL:    return SEM_STRING;
        case AST_CHAR_LITERAL:      return SEM_CHAR;
        case AST_BOOLEAN:           return SEM_BOOL;

        case AST_BINARY_EXPR: {
            SemanticType binary_type = binaryExprAnalyser(expressionAst, context);
            return binary_type;
        }

        case AST_FUNC_CALL: {
            SemanticType call_type = funcCallAnalyser(expressionAst, context);
            return call_type;
        }

        default:{
            printf("Unsupported expression in the %s at line %d\n", astTypeToString(expressionAst->ast_type), expressionAst->line);
            context->error_count++;
            return SEM_ERROR;
        }
    }
}