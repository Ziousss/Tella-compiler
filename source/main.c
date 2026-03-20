#include "../include/main.h"

int main (int argc, char **argv) {
    if (argc != 3) {
        // Usage {argv[0]} <FILE.c> <OUT>
        printf("Usage: ./compiler <FILE.c> <OUTPUT>\n");
        return 0;
    }

    printf("1. Reading file...\n"); fflush(stdout);
    char *source = readFile(argv[1]);
    if (source == NULL){
        printf("Fail to read the given file to compile.\n");
        return 1;
    }

    printf("2. Lexical analysis...\n"); fflush(stdout);
    Tokenstruct *tokenList = lexicalAnalyzer(source);
    if(tokenList == NULL){
        return 2;
    }
    free(source);

    int index = 0;
    printf("3. Parsing...\n"); fflush(stdout);
    ASTnode *programNode = programParse(tokenList, &index);
    if(programNode == NULL){
        printf("programNode is NULL\n");
        return 3;
    }

    //Frees tokenList
    freeTokenList(tokenList);

    printf("4. Semantic analysis...\n"); fflush(stdout);
    GlobalFunc *functions = programAnalyser(programNode);
    if(functions == NULL){
        cleanup(programNode, NULL, NULL);
        printf("Semantic error(s).\n");
        return 4;
    }

    //now all good for compilation.
    //Starting with the IR.
    printf("5. IR generation...\n"); fflush(stdout);
    IRstruct *IR = programIR(programNode, functions);
    if(IR == NULL){
        cleanup(programNode, functions, NULL);
        printf("Error in the IR creation.\n");
        return 5;
    }

    //Uncomment for better visualisation
    printIR(IR);

    //Now go on to the assembly code.
    printf("6. Assembly generation...\n"); fflush(stdout);
    bool created = mainAssemblyInstr(IR);
    if(!created){
        cleanup(programNode, functions, IR);
        printf("Failed to create a good assembly file.\n");
        return 6;
    }

    char *executable = argv[2];
    bool compiled = compileAssembly("../ASoutput.s", executable);

    if(!compiled){
        cleanup(programNode, functions, IR);
        printf("gcc compilation failed\n");
        return 1;
    }

    //Frees the AST
    printf("7. Starting freeing the nodes...\n"); fflush(stdout);
    cleanup(programNode, functions, IR);

    printf("Compilation successful!\n"); fflush(stdout);

    return 0;
}