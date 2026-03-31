#include "../include/assemblyInstr/builtInFunctions.h"    

void tellaPrint(FILE *output, ASContext *context){
    int offset = context->offset[0];
    int stringID = context->stringID[0];
    if(offset == 1){
        if(stringID == -1){
            printf("Constant given to tellaPrint but no access to its stringID.\n");
            context->errors++;
            return;
        }

        size_t size = context->size[stringID];
        fprintf(output, "lea rsi, [rip + string_%d]\n", stringID);
        fprintf(output,  "mov rdx, %ld\n", size);
    } else {
        printf("tellaPrint only for cst right now.\n");
        context->errors++;
        return;
    }

    fprintf(output,  "mov rdi, 1\n");
    fprintf(output,  "mov rax, 1\n");
    fprintf(output, "syscall\n");
}