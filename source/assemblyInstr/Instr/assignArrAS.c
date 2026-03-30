#include "../include/assemblyInstr/assemblyInstrHeader.h"

void assignArrAS(IRstruct *assignArr, FILE *output, StackLayout *stack, ASContext* context){
    Operand array = assignArr->data.assignArray.base;
    Operand index = assignArr->data.assignArray.index;
    Operand value = assignArr->data.assignArray.value;

    int arrOffset = getOffset(array, stack, context);
    int indexOffset = 0;
    int valueOffset = 0;
    if(index.IR_type != IR_CONST){
        indexOffset = getOffset(index, stack, context);
    } 
    if(value.IR_type != IR_CONST){
        valueOffset = getOffset(value, stack, context);
    }
    
    //load value in rbx
    if(valueOffset != 0){
        fprintf(output, "mov rbx, [rbp %+d]\n", valueOffset);
    } else {
        switch(value.data.IR_constant.cst_type){
            case IR_INT:
                fprintf(output, "mov rbx, %d\n", value.data.IR_constant.value.number);
                break;

            case IR_CHAR:
                fprintf(output, "mov rbx, %d\n", (int)value.data.IR_constant.value.chr);
                break;

            case IR_BOOL:
                fprintf(output, "mov rbx, %d\n", value.data.IR_constant.value.boolean);
                break;

            case IR_STRING:
                if(getSizeElement(array.data.IR_Variable.size) != 8){
                    printf("Cannot assign somehting else than a pointer to a string to an array of type string.\n");
                    context->errors++;
                    return;
                }
                int stringID = value.data.IR_constant.value.stringID;
                fprintf(output, "lea rbx, [rip + string_%d]\n", stringID);
                break;

            default: 
                printf("Unknown CstTypes in assignArrAS\n");
                context->errors++;
                return;
        }
    }

    if(indexOffset != 0){
        //load index in rax
        fprintf(output, "mov rax, [rbp %+d]\n", indexOffset);
    } else {
        switch (index.data.IR_constant.cst_type) {
        case IR_INT:
            fprintf(output, "mov rax, %d\n", index.data.IR_constant.value.number);
            break;
        
        default:
            printf("Index is not an INT but an %s in assignArrAS.\n", printCstType(index.data.IR_constant.cst_type));
            context->errors++;
            return;
        }
    }

    fprintf(output, "imul rax, %d\n", array.data.IR_Variable.elementSize);
    fprintf(output, "lea rcx, [rbp %+d]\n", arrOffset);
    fprintf(output, "sub rcx, rax\n");
    int size = array.data.IR_Variable.elementSize;

    if(size == 1){
        fprintf(output, "mov byte ptr [rcx], bl\n");
    }
    else if(size == 4){
        fprintf(output, "mov dword ptr [rcx], ebx\n");
    }
    else if(size == 8){
        fprintf(output, "mov qword ptr [rcx], rbx\n");
    }
    else{
        printf("Unsupported element size %d in assignArrAS\n", size);
        context->errors++;
    }

    return;
}