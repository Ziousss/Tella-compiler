#include "../include/assemblyInstr/builtInFunctions.h"    
    
void tellaPutChar(FILE *output, StackLayout *stack, ASContext *context){
    bool wasCst = false;
    switch (context->argType[0]){
        case IR_VAR:
        case IR_TMP:
        case IR_ARR:{

            int offsetRDI = context->offset[0];
            fprintf(output, "lea rsi, [rbp %+d]\n", offsetRDI);
            break;
        }
        case IR_CONST:{
            if(context->offset[0] != 1){
                printf("Unexpected error in tellaPutChar. Cst with offset = %d\n", context->offset[0]);
                context->errors++;
                return;
            }

            wasCst = true;
            stack->current_offset_count -= 8;
            int cstOffset = stack->current_offset_count;
            fprintf(output, "mov byte ptr [rbp %+d], dil\n", cstOffset);
            fprintf(output, "lea rsi, [rbp %+d]\n", cstOffset);

            break;
        }
        default:
            printf("Op given to defineCompilerFunctions is unknown.\n");
            context->errors++;
            return;
        }

    fprintf(output, "mov rdi, 1\n");
    fprintf(output, "mov rax, 1\n");
    fprintf(output, "mov rdx, 1\n");
    fprintf(output, "syscall\n");

    if(wasCst == true){
        //freeing the space on the stack since it is just a cst.
        stack->current_offset_count += 8;
    }
}