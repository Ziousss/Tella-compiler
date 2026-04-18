#include "../include/main.h"

int main (int argc, char **argv) {
    if(strcmp("-h", argv[1]) == 0 || strcmp("-help", argv[1]) == 0){
        printf("Usage: ./compiler -f <FILE(S).c> -o <OUTPUT>\n");
        printf("After this command, you can use several other commands to better visualise the process.\n\n");
        printf("-So: Prints the source code before preprocessing.\n");
        printf("-Pr: Prints the source code after preprocessing.\n");
        printf("-L: Shows you the lexer output.\n");
        printf("-Pa: Shows you the parser output.\n");
        printf("-I: Shows you the IR output.\n");
        printf("-St: Shows you the stack layout of all functions in the files.\n");
        printf("-A: Shows you the created assembly file.\n");
        return 0;
    }

    if (argc < 5) {
        // Usage {argv[0]} <FILE.c> <OUT>
        printf("Usage: ./compiler -f <FILE.c> -o <OUTPUT> [command1] [command2] etc\n");
        printf("For more informations: ./compiler -h or ./compiler -help\n");
        return 0;
    }

    MainContext *contextMain = contextInit(argv, argc); 
    if(contextMain == NULL || contextMain->errors != 0){
        return -1;
    }

    printf("1. Reading file...\n"); fflush(stdout);
    size_t sourceLen = 0;
    size_t argvIndex = 2;
    char *source = NULL;

    while(strcmp(argv[argvIndex], "-o") != 0){
        char *tmp = readFile(argv[argvIndex]);
        if (tmp == NULL){
            printf("Fail to read the given file to compile.\n");
            if(source != NULL) free(source);
            return 1;
        }
        size_t tmpLen = strlen(tmp);
        char *newSource = realloc(source, sourceLen + tmpLen + 1);
        if(newSource == NULL){
            printf("Realloc failed for newSource in main.\n");
            if(source != NULL) free(source);
            free(tmp);
            return 50;
        }

        source = newSource;
        memcpy(source + sourceLen, tmp, tmpLen);
        sourceLen += tmpLen;
        source[sourceLen] = '\0';
        free(tmp);
        tmp = NULL;
        argvIndex++;
    }
    size_t outputFileIndex = ++argvIndex;

    if(contextMain->source) {
        printf("\n%s\n\n", source);
    }
    
    printf("2. Preprocessing the source file...\n"); fflush(stdout);
    char *originalFileName = argv[1];
    PreResult preprocessStruct = preprocess(source, originalFileName);
    free(source);
    if(preprocessStruct.size == 0){
        cleanup(NULL, NULL, NULL, contextMain, NULL);
        return 40;
    }
    
    if(contextMain->postSource){
        printf("\n");
        for(size_t i = 0; i < preprocessStruct.size; i++){
            printf("%c", preprocessStruct.data[i].c);
        }
        printf("\n");
    }

    printf("3. Lexical analysis...\n"); fflush(stdout);
    Tokenstruct *tokenList = lexicalAnalyzer(preprocessStruct);
    if(tokenList == NULL){
        cleanup(NULL, NULL, NULL, contextMain, NULL);
        return 3;
    }


    if(contextMain->lexer) {
        printf("\n");
        printLexer(tokenList);
        printf("\n");
    }

    int index = 0;
    printf("4. Parsing...\n"); fflush(stdout);
    ASTnode *programNode = programParse(tokenList, &index);
    if(programNode == NULL){
        printf("programNode is NULL\n");
        cleanup(NULL, NULL, NULL, contextMain, tokenList);
        return 4;
    }

    for(size_t i = 0; i < preprocessStruct.size; i++){
        free(preprocessStruct.data[i].fileName);
    }
    free(preprocessStruct.data);

    if(contextMain->parser){
        printf("\n");
        print_ast(programNode, 0);
        printf("\n");
    }

    printf("5. Semantic analysis...\n"); fflush(stdout);
    GlobalFunc *functions = programAnalyser(programNode);
    if(functions == NULL){
        cleanup(programNode, NULL, NULL,contextMain, tokenList);
        printf("Semantic error(s).\n");
        return 5;
    }

    //now all good for compilation.
    //Starting with the IR.
    printf("6. IR generation...\n"); fflush(stdout);
    IRstruct *IR = programIR(programNode, functions);
    if(IR == NULL){
        cleanup(programNode, functions, NULL, contextMain, tokenList);
        return 6;
    }

    if(contextMain->IR){
        printf("\n");
        printIR(IR);
        printf("\n");
    }

    //Now go on to the assembly code.
    printf("7. Assembly generation...\n"); fflush(stdout);
    int errors = mainAssemblyInstr(IR, contextMain->stackLayout);
    if(errors != 0){
        cleanup(programNode, functions, IR, contextMain, tokenList);
        printf("Failed to create a good assembly file.\n");
        return 7;
    }

    char *executable = argv[outputFileIndex];
    bool compiled = compileAssembly("ASoutput.s", executable);

    if(!compiled){
        cleanup(programNode, functions, IR, contextMain, tokenList);
        printf("gcc compilation failed\n");
        return 100;
    }

    if(contextMain->assembly){
        char *assembly = readFile("ASoutput.s");
        printf("\n%s\n", assembly);
        printf("The original file has not been destroyed so you can inspect it directly as well.\n\n");
        free(assembly);
    }

    //Frees Everything
    printf("8. Starting freeing the nodes...\n"); fflush(stdout);
    cleanup(programNode, functions, IR, contextMain, tokenList);

    printf("Compilation successful!\n"); fflush(stdout);

    return 0;
}