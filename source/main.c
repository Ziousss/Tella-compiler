#include "../include/lexer/tokenizer.h"
#include "../include/lexer/readFile.h"
#include "../include/parser/grammarRules.h"

int main (int argc, char **argv) {
    if (argc > 3 || argc == 1) {
        perror("You need 2 arguments");
        return 0;
    }

    char *source = readFile(argv[1]);
    if (source == NULL){
        return 1;
    }

    Tokenstruct *tokenList = lexicalAnalyzer(source);
    free(source);

    int index = 0;
    ASTnode *programNode = programParse(tokenList, &index);
    if(programNode == NULL){
        printf("programNode is NULL\n");
        return 1;
    }

    return 0;

}