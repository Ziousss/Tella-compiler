#include "../include/IntermediateRep/IRheader.h"

void blockIR(ASTnode *block, IRContext *context){
    ASTnode *stmt = block->data.block.stmts;
    while(stmt != NULL){
        NodeType type = stmt->ast_type;
        switch (type){
            case AST_VAR_DECL: {
                if(stmt->data.declaration.expression == NULL){
                    break;
                }

                Operand dst;
                dst.IR_type = IR_VAR;
                dst.data.IR_Variable.identifier = stmt->data.declaration.identifier;

                Operand src = expressionIR(stmt->data.declaration.expression, context);

                IRstruct *declaration = newAssign(context, dst, src);
                emit(declaration, context);

                break;
            }
            case AST_ASSIGN_EXPR: {
                Operand dst;
                dst.IR_type = IR_VAR;
                dst.data.IR_Variable.identifier = stmt->data.assign.target;

                Operand src = expressionIR(stmt->data.assign.value, context);

                IRstruct *declaration = newAssign(context, dst, src);
                emit(declaration, context);

                break;
            }
            case AST_RETURN:{
                returnIR(stmt, context);
                break;
            }
            case AST_WHILE_STMT: {
                whileIR(stmt, context);
                break;
            }
            case AST_FOR_STMT: {
                forIR(stmt, context);
                break;
            }
            case AST_IF_STMT: {
                ifIR(stmt, context);
                break;
            }
            default: {
                printf("Forgot to add the ast %s to blockIR.\n", astTypeToString(type));
                context->errors++;
                break;
            }
        }

        stmt = stmt->next;
    }
} 