#include "../include/IntermediateRep/IRheader.h"

Operand funcCallIR(ASTnode *funcCall, IRContext *context){
    char *funcName = funcCall->data.func_call.name;
    const GlobalFunc *function = findFuncDef(funcName);
    if(function == NULL && !compilerDefined(funcName)){
        printf("Function %s is called but never defined.\n", funcName);
        context->errors++;
        return (Operand){0};
    }

    ArgNode *arg = funcCall->data.func_call.args;
    int argNumber = 0;
    while(arg != NULL){
        int error = context->errors;
        Operand value = expressionIR(arg->expression, context);
        if(context->errors != error){
            return(Operand){0};
        
        }
        IRstruct *argument = newArg(context, value);
        if(argument == NULL){
            return (Operand){0};
        }
        emit(argument, context);

        argNumber++;
        arg = arg->next;
    }

    Operand ret;
    CstTypes ret_type;
    if(!compilerDefined(funcName)) {
        ret_type = fromSemToIRTypes(function->type);
    } else {
        ret_type = retTypeCompilerDefined(funcName);
        if(ret_type == IR_CST_ERROR){
            context->errors++;
            return (Operand){.IR_type = IR_OPERAND_ERROR};
        }
    }
 
    if(ret_type != IR_VOID){
        ret = newTmp(ret_type, context);
    } else {
        ret = (Operand){.IR_type = IR_VOID_OPERAND};
    }

    IRstruct *call = newCall(context, funcName, argNumber, ret);
    emit(call, context);
    return ret;
}