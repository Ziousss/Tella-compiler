#include "../include/IntermediateRep/helperFuncIR.h"

static GlobalFunc *definedFunc = NULL;

void initGlobalFunctions(GlobalFunc *funcs) {
    definedFunc = funcs;
}

GlobalFunc *findFuncDef(char *name){
    GlobalFunc *tmp = definedFunc;
    while (tmp != NULL) {
        if(strcmp(name, tmp->name) == 0){
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

void emit(IRstruct *to_add, IRContext *context){
    to_add->next = NULL;

    if(context->head == NULL){
        context->head = to_add;
        context->tail = to_add;
        return;
    }

    context->tail->next = to_add;
    context->tail = to_add;
}

IRstruct *newArg(IRContext *context, Operand arg){
    IRstruct *new = malloc(sizeof(IRstruct));
    if(new == NULL){
        printf("Malloc error in newArg.\n");
        context->errors++;
        return NULL;
    }

    new->next = NULL;
    new->data.arg.value = arg;
    new->op = IR_ARG;

    return new;
}

IRstruct *newCall(IRContext *context, char *name, int count, Operand dst){
    IRstruct *new = malloc(sizeof(IRstruct));
    if(new == NULL){
        printf("Malloc error in newCall.\n");
        context->errors++;
        return NULL;
    }

    new->next = NULL;
    new->op = IR_CALL;
    new->data.call.arg_count = count;
    new->data.call.dst = dst;
    new->data.call.func_name = name;

    return new;
}

IRstruct *newLabel(IRContext *context, int label){
    IRstruct *new = malloc(sizeof(IRstruct));
    if(new == NULL){
        printf("Malloc error in newLabel.\n");
        context->errors++;
        return NULL;
    }

    new->next = NULL;
    new->op = IR_LABEL;
    new->data.label.label_id = label;

    return new;
}

IRstruct *newFunc(IRContext *context, char *name_func){
    IRstruct *new = malloc(sizeof(IRstruct));
    if(new == NULL){
        printf("Malloc error in newFunc.\n");
        context->errors++;
        return NULL;
    }

    new->data.function.name_func = name_func;
    new->next = NULL;
    new->op = IR_FUNC;

    return new;
}

IRstruct *newBinary(IRContext *context, Operand dst, Operand src1, Operand src2, IRoperation op){
    IRstruct *new = malloc(sizeof(IRstruct));
    if(new == NULL){
        printf("Malloc error in newBinary.\n");
        context->errors++;
        return NULL;
    }

    new->next = NULL;
    new->op = op;
    new->data.binary.dst = dst;
    new->data.binary.src1 = src1;
    new->data.binary.src2 = src2;

    return new;
}

IRstruct *newJmp(IRContext *context, int target){
    IRstruct *new = malloc(sizeof(IRstruct));
    if(new == NULL){
        printf("Malloc error in newJmp to taget %d.\n", target);
        context->errors++;
        return NULL;
    }

    new->next = NULL;
    new->op = IR_JMP;
    new->data.jump.target_label = target;

    return new;
}

IRstruct *newJmpFalse(IRContext *context, int end_label, Operand condition){
    IRstruct *new = malloc(sizeof(IRstruct));
    if(new == NULL){
        printf("Malloc error in newJmpFalse to taget %d.\n", end_label);
        context->errors++;
        return NULL;
    }

    new->next = NULL;
    new->op = IR_JMP_FALSE;
    new->data.condition_jump.target_label = end_label;
    new->data.condition_jump.condition = condition;

    return new;
}

IRstruct *newParam(IRContext *context, int index, char *name, CstTypes type){
    IRstruct *new = malloc(sizeof(IRstruct));
    if(new == NULL){
        printf("Malloc error in newParam.\n");
        context->errors++;
        return NULL;
    }

    new->data.parameters.parameter.data.IR_Variable.param_index = index;
    new->data.parameters.parameter.IR_type = IR_VAR;
    new->data.parameters.parameter.data.IR_Variable.paramType = type;
    new->data.parameters.parameter.data.IR_Variable.identifier = strdup(name);
    new->next = NULL;
    new->op = IR_PARAM;
    return new;
}

IRstruct *newReturn(IRContext *context, Operand target){
    IRstruct *new = malloc(sizeof(IRstruct));
    if(new == NULL){
        printf("Malloc error in newReturn.\n");
        context->errors++;
        return NULL;
    }

    new->next = NULL;
    new->op = IR_RET;
    new->data.ret.return_value = target;

    return new;
}

IRstruct *newAssign(IRContext *context, Operand dst, Operand src){
    IRstruct *new = malloc(sizeof(IRstruct));
    if(new == NULL){
        printf("Malloc error in newAssign to taget.\n");
        context->errors++;
        return NULL;
    }

    new->op = IR_ASSIGN;
    new->next = NULL;
    new->data.assign.dst = dst;
    new->data.assign.src = src;

    return new;
}

IRstruct *newAssignArray(IRContext *context, Operand base, Operand value, Operand index){
    IRstruct *new = malloc(sizeof(IRstruct));
    if(new == NULL){
        printf("Malloc error in newAssignArray to taget.\n");
        context->errors++;
        return NULL;
    }

    new->op = IR_ASSIGN_ARR;
    new->next = NULL;
    new->data.assignArray.base = base;
    new->data.assignArray.value = value;
    new->data.assignArray.index = index;

    return new;
}

IRstruct *newArrayLoad(IRContext *context, Operand base, Operand index, Operand tmp){
    IRstruct *new = malloc(sizeof(IRstruct));
    if(new == NULL){
        printf("Malloc error in newAssignArray to taget.\n");
        context->errors++;
        return NULL;
    }

    new->op = IR_LOAD_ARRAY;
    new->next = NULL;
    new->data.loadArray.base = base;
    new->data.loadArray.dst = tmp;
    new->data.loadArray.index = index;

    return new;
}

Operand newString(int stringID){
    Operand op;

    op.IR_type = IR_CONST;
    op.data.IR_constant.cst_type = IR_STRING;
    op.data.IR_constant.value.stringID = stringID;

    return op;
}

Operand newChar(char value){
    Operand op;

    op.IR_type = IR_CONST;
    op.data.IR_constant.cst_type = IR_CHAR;
    op.data.IR_constant.value.chr = value;

    return op;
}

Operand newBool(bool value){
    Operand op;

    op.IR_type = IR_CONST;
    op.data.IR_constant.cst_type = IR_BOOL;
    op.data.IR_constant.value.boolean = value;

    return op;
}

Operand newInt(int value){
    Operand op;

    op.IR_type = IR_CONST;
    op.data.IR_constant.cst_type = IR_INT;
    op.data.IR_constant.value.number = value;

    return op;
}

Operand newTmp(CstTypes type, IRContext *context){
    Operand tmp;
    tmp.IR_type = IR_TMP;
    tmp.data.IR_tmp.id_tmp = context->current_tmp++;
    tmp.data.IR_tmp.type = type;

    return tmp;
}

IRoperation fromTokToIRtype(Tokentype type){
    switch (type){
        case TOK_MINUS:                 return IR_SUB;
        case TOK_PLUS:                  return IR_ADD;
        case TOK_STAR:                  return IR_MULT;
        case TOK_SLASH:                 return IR_DIV;
        case TOK_GR:                    return IR_GR;
        case TOK_GREQ:                  return IR_GREQ;
        case TOK_LESS:                  return IR_LESS;
        case TOK_LESSEQ:                return IR_LESSEQ;
        case TOK_EQEQ:                  return IR_EQEQ;
        case TOK_UNEQ:                  return IR_UNEQ;

        default:                return IR_ERROR;
    }
}

CstTypes fromTokToCstType(Tokentype type){
    switch (type){
        case TOK_INT:
        case TOK_INTEGER_LITERAL:       return IR_INT;
        case TOK_SIZET:                 return IR_SIZET;
        case TOK_CHAR:
        case TOK_CHAR_LITERAL:          return IR_CHAR;
        case TOK_STRING:
        case TOK_STRING_LITERAL:        return IR_STRING;
        case TOK_TRUE:
        case TOK_FALSE:                 return IR_BOOL;
        case TOK_VOID:                  return IR_VOID;
        default:                        return IR_CST_ERROR;
    }
}

CstTypes fromSemToIRTypes(SemanticType type){
    switch (type){
        case SEM_INT:           return IR_INT;
        case SEM_CHAR:          return IR_CHAR;
        case SEM_SIZET:         return IR_SIZET;
        case SEM_STRING:        return IR_STRING;
        case SEM_VOID:          return IR_VOID;
        case SEM_BOOL:          return IR_BOOL;

        default:                return IR_CST_ERROR;
    }
}

//Unused
const char *printCstType(CstTypes type){
    switch (type){
        case IR_STRING:     return "IR_string";
        case IR_INT:        return "IR_int";
        case IR_CHAR:       return "IR_char";
        case IR_BOOL:       return "IR_bool";
        case IR_VOID:       return "IR_void";
        case IR_SIZET:      return "IR_size_t";

        default:            return "CSTtype not named yet";
    }
}

bool isbool(IRoperation op){
    return (op == IR_GR || op == IR_GREQ || op == IR_LESS
            || op == IR_LESSEQ || op == IR_EQEQ || op == IR_UNEQ);
}

int getSizeElement(SemanticType type){
    switch (type){
        case SEM_CHAR:      return 1;
        case SEM_BOOL:      return 1;
        case SEM_INT:       return 4;

        default: {
            printf("Unknown type in getSizeElement.\n");
            return -1;
        }
    }
}

IRsymbole *findDecl(char *name, IRContext *context){
    IRsymbole *cur = context->IRsym;
    while(cur != NULL){
        if(strcmp(name, cur->name) == 0){
            return cur;
        }

        cur = cur->next;
    }

    return NULL;
}