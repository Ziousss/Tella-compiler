#include "../include/assemblyInstr/assemblyInstrHeader.h"

//return a bool to know whether it worked or not.
bool assemblyInstr(IRstruct *IRlist){
    bool opened = false;
    FILE *output = fopen("ASoutput.s", "w");
    if(output == NULL){
        printf("File ASoutput.s did not open correctly.\n");
        return opened;
    }

    opened = true;
    programMC(IRlist, output);

    return opened;
}