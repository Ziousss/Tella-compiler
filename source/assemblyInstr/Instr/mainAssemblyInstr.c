#include "../include/assemblyInstr/assemblyInstrHeader.h"

//returns a bool to know whether it worked or not.
int mainAssemblyInstr(IRstruct *IRlist, bool stackLayoutBool){
    ASContext* context = malloc(sizeof(ASContext));
    if(context == NULL){
        printf("Malloc error in mainAssemblyInstr.\n");
        return 1;
    }
    context->errors = 0;

    FILE *output = fopen("ASoutput.s", "w");
    if(output == NULL){
        printf("File ASoutput.s did not open correctly.\n");
        fflush(stdout);
        return context->errors++;
    }

    fprintf(output, ".intel_syntax noprefix\n.globl main\n");
    programAS(IRlist, output, context, stackLayoutBool);
    fprintf(output, ".section .note.GNU-stack,\"\",@progbits\n");
    fclose(output);

    int errors = context->errors;
    free(context);
    return errors;
}