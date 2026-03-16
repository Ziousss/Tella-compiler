#include "../include/main.h"

int main (int argc, char **argv) {
    if (argc != 2) {
        perror("You need 2 arguments, the first being the compiler's binary and second being the file to compile.\n");
        return 0;
    }

    char *source = readFile(argv[1]);
    if (source == NULL){
        printf("Fail to read the given file to compile.\n");
        return 1;
    }

    Tokenstruct *tokenList = lexicalAnalyzer(source);
    if(tokenList == NULL){
        return 2;
    }
    free(source);

    int index = 0;
    ASTnode *programNode = programParse(tokenList, &index);
    if(programNode == NULL){
        printf("programNode is NULL\n");
        return 3;
    }
    free(tokenList);

    GlobalFunc *functions = programAnalyser(programNode);
    if(functions == NULL){
        printf("Semantic error(s).\n");
        return 4;
    }

    //now all good for compilation.
    //Starting with the IR.
    IRstruct *IR = programIR(programNode, functions);
    if(IR == NULL){
        printf("Error in the IR creation.\n");
        return 5;
    }
    printIR(IR);

    //Now go on to the assembly code.
    

    return 0;
}