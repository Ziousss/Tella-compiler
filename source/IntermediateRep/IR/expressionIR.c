#include "../include/IntermediateRep/IRheader.h"

Operand expressionIR(ASTnode *expression, IRContext *context){
    NodeType type = expression->ast_type;
    switch(type){
        case AST_IDENTIFIER: {
            Operand variable;
            variable.IR_type = IR_VAR;
            variable.data.IR_Variable.identifier = expression->data.identifier.name;

            return variable;
        }
        case AST_STRING_LITERAL: {
            Operand string = newString(expression->data.string_literal.string);
            return string;
        }
        case AST_CHAR_LITERAL: {
            Operand chr = newChar(expression->data.character_literal.character);
            return chr;
        }
        case AST_NUMBER: {
            Operand number = newInt(expression->data.int_literal.value);
            return number;
        }
        case AST_BOOLEAN: {
            Operand boolean = newBool(expression->data.boolean_literal.boolean);
            return boolean;
        }
        case AST_BINARY_EXPR: {
            Operand left = expressionIR(expression->data.binary.left, context);
            Operand right = expressionIR(expression->data.binary.right, context);
            IRoperation op = fromTokToIRtype(expression->data.binary.op);

            Operand tmp = newTmp(context);

            IRstruct *binary = newBinary(context, tmp, left, right, op);
            emit(binary, context);
            return tmp;
        }
        default: {
            printf("The ast %s has not been cover by expressionIR yet.\n", astTypeToString(type));
            context->errors++;
            return (Operand){0};
        }
    }
}