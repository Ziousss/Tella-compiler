#include "../include/lexer/tokenizer.h"
#include "../include/lexer/readFile.h"

int main (int argc, char **argv) {
    if (argc > 3 || argc == 1) {
        perror("You need 2 arguments");
        return 0;
    }

    char *source = readFile(argv[1]);
    if (source == NULL){
        return 1;
    }

    Tokenstruct *token = lexicalAnalyzer(source);
    free(source);
}