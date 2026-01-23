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
        }

        stmt = stmt->next;
    }
} 