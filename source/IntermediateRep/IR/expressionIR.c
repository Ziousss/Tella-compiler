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

            Operand tmp;
            if(isbool(op)){
                tmp = newTmp(IR_BOOL, context);
            } else {
                tmp = newTmp(IR_INT, context);
            }

            IRstruct *binary = newBinary(context, tmp, left, right, op);
            emit(binary, context);
            return tmp;
        }
        case AST_FUNC_CALL: {
            Operand func_ret = funcCallIR(expression, context);
            return func_ret;
        }
        case AST_ARRAY_LOAD:{
            Operand index = expressionIR(expression->data.arrayLoad.index, context);
            if(index.IR_type == IR_TMP && index.data.IR_tmp.type != IR_INT){
                printf("Index did not return and INT.\n");
                context->errors++;
                return (Operand){0};
            }

            IRsymbole *sym = findDecl(expression->data.arrayLoad.name, context);
            if(sym == NULL){
                printf("Could not find any declaration for \"%s\".\n", expression->data.arrayLoad.name);
                context->errors++;
                return (Operand){0};
            }

            int size = sym->size;
            if(size == -1){
                printf("\"%s\" is thought to be an array but it is not.", expression->data.arrayLoad.name);
                context->errors++;
                return (Operand){0};
            }

            Operand base;
            base.IR_type = IR_ARR;
            base.data.IR_Variable.identifier = expression->data.arrayLoad.name;
            base.data.IR_Variable.size = size;
            base.data.IR_Variable.elementSize = getSizeElement(sym->type);

            Operand tmp = newTmp(fromSemToIRTypes(sym->type), context);
            
            IRstruct *arrayLoad = newArrayLoad(context, base, index, tmp);
            emit(arrayLoad, context);

            return tmp;
        }
        default: {
            printf("The ast %s has not been cover by expressionIR yet.\n", astTypeToString(type));
            context->errors++;
            return (Operand){0};
        }
    }
}