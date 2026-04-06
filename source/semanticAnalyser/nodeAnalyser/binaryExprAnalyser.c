#include "../include/semanticAnalyser/nodeAnalyser.h"

SemanticType binaryExprAnalyser(ASTnode *binary, SemContext *context){
    SemanticType left = expressionAnalyser(binary->data.binary.left, context);
    SemanticType right = expressionAnalyser(binary->data.binary.right, context);
    if(left == SEM_ERROR || right == SEM_ERROR){
        return SEM_ERROR;
    }

    if(left == SEM_STRING && right == SEM_STRING ){
        printf("Binary operation on line %ld file %s cannot have only type CHAR *.\n", binary->line, binary->fileName);
        context->error_count++;
        return SEM_ERROR;
    }

    Tokentype op = binary->data.binary.op;
    if(isCalculus(op)){
        if(left == SEM_INT && right == SEM_INT){
            return SEM_INT;
        }
        if(left == SEM_SIZET && right == SEM_SIZET){
            return SEM_SIZET;
        }

        if(compSizeTInt(left, right) == 1){
            if(binary->data.binary.left->ast_type != AST_NUMBER && binary->data.binary.right->ast_type != AST_NUMBER){
                printf("Warning: binary Operation between size_t and integer in line %ld file %s.\n", binary->line, binary->fileName);
            }
            return SEM_INT;
        }

        printf("Arithmetic operator %s line %ld file %s can only take two ints; here left is type %s and right is type %s.\n", tokenTypeToString(binary->data.binary.op), binary->line, binary->fileName, fromSemToString(left), fromSemToString(right));
        context->error_count++;
        return SEM_ERROR;
    }
    else if(isBool(op)){
        if((left == SEM_BOOL && right == SEM_BOOL) || (left == SEM_INT && compSizeTInt(left, right) == 0) || compSizeTInt(left, right) == 1){
            return SEM_BOOL;
        }
        printf("Comparison operator %s line %ld file %s can only take two ints; here leftside is type %s and rightside is type %s.\n", tokenTypeToString(binary->data.binary.op), binary->line, binary->fileName, fromSemToString(left), fromSemToString(right));
        context->error_count++;
        return SEM_ERROR;
    }
    else if(op == TOK_AND || op == TOK_OR){
        if(left == SEM_BOOL && right == SEM_BOOL){
            return SEM_BOOL;
        }
        printf("The %s operator line %ld file %s need two bool type; here leftside is type %s and rightside is type %s.\n", tokenTypeToString(binary->data.binary.op), binary->line, binary->fileName, fromSemToString(left), fromSemToString(right));
        context->error_count++;
        return SEM_ERROR;
    }
    else if(op == TOK_EQEQ || op == TOK_UNEQ){
        if(left == right){
            return SEM_BOOL;
        }
        printf("The %s operator line %ld file %s need two identifier with the same type; here leftside is type %s and rightside is type %s.\n", tokenTypeToString(binary->data.binary.op), binary->line, binary->fileName, fromSemToString(left), fromSemToString(right));
        context->error_count++;
        return SEM_ERROR;
    }
    printf("Unknown binary operator %s at line %ld file %s.\n", tokenTypeToString(op), binary->line, binary->fileName);
    context->error_count++;
    return SEM_ERROR;
}