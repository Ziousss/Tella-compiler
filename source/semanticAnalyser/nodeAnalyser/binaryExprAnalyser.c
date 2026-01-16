#include "../include/semanticAnalyser/nodeAnalyser.h"

SemanticType binaryExprAnalyser(ASTnode *binary, SemContext *context){
    SemanticType left = expressionAnalyser(binary->data.binary.left, context);
    SemanticType right = expressionAnalyser(binary->data.binary.right, context);
    if(left == SEM_ERROR || right == SEM_ERROR){
        return SEM_ERROR;
    }

    Tokentype op = binary->data.binary.op;
    if(isCalculus(op)){
        if(left == SEM_INT && right == SEM_INT){
            return SEM_INT;
        }
        printf("Arithmetic operator %s line %d can only take two ints; here left is type %s and right is type %s.\n", tokenTypeToString(binary->data.binary.op), binary->line, fromSemToString(left), fromSemToString(right));
        context->error_count++;
        return SEM_ERROR;
    }
    else if(isBool(op)){
        if(left == SEM_INT && right == SEM_INT){
            return SEM_BOOL;
        }
        printf("Comparison operator %s line %d can only take two ints; here leftside is type %s and rightside is type %s.\n", tokenTypeToString(binary->data.binary.op), binary->line, fromSemToString(left), fromSemToString(right));
        context->error_count++;
        return SEM_ERROR;
    }
    else if(op == TOK_AND || op == TOK_OR){
        if(left == SEM_BOOL && right == SEM_BOOL){
            return SEM_BOOL;
        }
        printf("The %s operator line %d need two bool type; here leftside is type %s and rightside is type %s.\n", tokenTypeToString(binary->data.binary.op), binary->line, fromSemToString(left), fromSemToString(right));
        context->error_count++;
        return SEM_ERROR;
    }
    else if(op == TOK_EQEQ || op == TOK_UNEQ){
        if(left == right){
            return SEM_BOOL;
        }
        printf("The %s operator line %d need two identifier with the same type; here leftside is type %s and rightside is type %s.\n", tokenTypeToString(binary->data.binary.op), binary->line, fromSemToString(left), fromSemToString(right));
        context->error_count++;
        return SEM_ERROR;
    }
    printf("Unknown binary operator %s at line %d.\n", tokenTypeToString(op), binary->line);
    context->error_count++;
    return SEM_ERROR;

}