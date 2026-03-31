#include "../include/assemblyInstr/builtInFunctions.h"    

void tellaPrint(FILE *output, ASContext *context){
    int offset = context->offset[0];
    int stringID = context->stringID[0];
    IRstruct *rodata = getRodataString(context, stringID, NULL);
    if(rodata == NULL){
        printf("Rodata is null in tellaPrint\n");
        context->errors++;
        return;
    }

    size_t size = strlen(rodata->data.rodata.string);

    if(offset == 1){
        if(stringID == -1){
            printf("Constant given to tellaPrint but no access to its stringID.\n");
            context->errors++;
            return;
        }

        fprintf(output, "lea rsi, [rip + string_%d]\n", stringID);
        fprintf(output,  "mov rdx, %ld\n", size);
    } else {
        fprintf(output, "mov rsi, [rbp %+d]\n", offset);
        fprintf(output, "mov rdx, %ld\n", size);
    }

    fprintf(output, "mov rdi, 1\n");
    fprintf(output, "mov rax, 1\n");
    fprintf(output, "syscall\n");
}