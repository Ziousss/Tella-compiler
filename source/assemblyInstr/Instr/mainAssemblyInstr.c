#include "../include/assemblyInstr/assemblyInstrHeader.h"

//return a bool to know whether it worked or not.
bool mainAssemblyInstr(IRstruct *IRlist){
    bool opened = false;
    FILE *output = fopen("../ASoutput.s", "w");
    if(output == NULL){
        printf("File ASoutput.s did not open correctly.\n");
        fflush(stdout);
        return opened;
    }

    opened = true;
    fprintf(output, ".intel_syntax noprefix\n.globl main\n");
    programAS(IRlist, output);
    fprintf(output, ".section .note.GNU-stack,\"\",@progbits\n");
    fclose(output);

    return opened;
}