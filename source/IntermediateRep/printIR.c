#include "../include/IntermediateRep/printIR.h"

void printIR(IRstruct *IR){
    IRstruct *tmp = IR;

    while(tmp != NULL){
        switch(tmp->op){
            case IR_ARG:
                printf("ARG ");
                printOperand(tmp->data.arg.value);
                printf("\n");
                break;

            case IR_CALL:
                if(tmp->data.call.dst.IR_type == IR_TMP){
                    printOperand(tmp->data.call.dst);
                    printf(" = ");
                }

                printf("CALL %s %d\n",
                       tmp->data.call.func_name,
                       tmp->data.call.arg_count);
                break;

            case IR_RET:
                printf("RET ");
                printOperand(tmp->data.ret.return_value);
                printf("\n");
                break;

            case IR_ADD:
            case IR_SUB:
            case IR_MULT:
            case IR_DIV:
            case IR_EQEQ:
            case IR_UNEQ:
            case IR_GR:
            case IR_GREQ:
            case IR_LESS:
            case IR_LESSEQ:

                printOperand(tmp->data.binary.dst);
                printf(" = ");
                printOperand(tmp->data.binary.src1);

                switch(tmp->op){
                    case IR_ADD: printf(" + "); break;
                    case IR_SUB: printf(" - "); break;
                    case IR_MULT: printf(" * "); break;
                    case IR_DIV: printf(" / "); break;
                    case IR_EQEQ: printf(" == "); break;
                    case IR_UNEQ: printf(" != "); break;
                    case IR_GR: printf(" > "); break;
                    case IR_GREQ: printf(" >= "); break;
                    case IR_LESS: printf(" < "); break;
                    case IR_LESSEQ: printf(" <= "); break;
                    default: break;
                }

                printOperand(tmp->data.binary.src2);
                printf("\n");
                break;

            case IR_ASSIGN:
                printOperand(tmp->data.binary.dst);
                printf(" = ");
                printOperand(tmp->data.binary.src1);
                printf("\n");
                break;

            case IR_LABEL:
                printf("L%d:\n", tmp->data.label.label_id);
                break;

            case IR_JMP:
                printf("JMP L%d\n", tmp->data.jump.target_label);
                break;

            case IR_JMP_FALSE:
                printf("JMP_FALSE ");
                printOperand(tmp->data.condition_jump.condition);
                printf(" L%d\n", tmp->data.condition_jump.target_label);
                break;

            default:
                printf("UNKNOWN IR OP\n");
                break;
        }

        tmp = tmp->next;
    }
}

void printOperand(Operand op){
    switch(op.IR_type){
        case IR_VAR:
            printf("%s", op.data.IR_Variable.identifier);
            break;

        case IR_TMP:
            printf("t%d", op.data.IR_tmp.id_tmp);
            break;

        case IR_CONST:
            switch(op.data.IR_constant.cst_type){
                case IR_INT:
                    printf("%d", op.data.IR_constant.value.number.number);
                    break;

                case IR_CHAR:
                    printf("'%c'", op.data.IR_constant.value.chr.chr);
                    break;

                case IR_STRING:
                    printf("\"%s\"", op.data.IR_constant.value.string.string);
                    break;

                case IR_BOOL:
                    printf("%s",
                        op.data.IR_constant.value.boolean.boolean ? "true" : "false");
                    break;

                case IR_VOID:
                    printf("void");
                    break;
            }
            break;
        default:
            printf("UNKNOWN_OPERAND");
            break;
    }
}