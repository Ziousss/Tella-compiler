#include "../include/main.h"

int main (int argc, char **argv) {
    if (argc != 2) {
        perror("You need 2 arguments, the first being the compiler file and second being the file to compile.\n");
        return 0;
    }

    char *source = readFile(argv[1]);
    if (source == NULL){
        printf("Fail to read the given file to compile.\n");
        return 1;
    }

    Tokenstruct *tokenList = lexicalAnalyzer(source);
    if(tokenList == NULL){
        return 1;
    }
    free(source);

    int index = 0;
    ASTnode *programNode = programParse(tokenList, &index);
    if(programNode == NULL){
        printf("programNode is NULL\n");
        return 1;
    }
    free(tokenList);

    GlobalFunc *functions = programAnalyser(programNode);
    if(functions == NULL){
        printf("Semantics error.\n");
        return 1;
    }
    printf("Semantic is good.\n");  

    //now all good for compilation
    IRstruct *IR = programIR(programNode, functions);
    printIR(IR);

    return 0;
}