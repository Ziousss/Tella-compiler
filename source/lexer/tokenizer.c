#include "../include/lexer/tokenizer.h"
#include "../include/lexer/charcheck.h"

const char* tokenTypeToString(int type) {
    switch (type) {
        case IDENTIFIER: return "IDENTIFIER";
        case KEYWORD:    return "KEYWORD";
        case OPERATOR:   return "OPERATOR";
        case DELIMITER:  return "DELIMITER";
        case INTEGER:    return "INTEGER";
        case UNIDENTIFIED: return "UNIDENTIFIED";
        default: return "UNKNOWN";
    }
}

int lexicalAnalyzer (char* input) {
    int left = 0, right = 0;
    int len = strlen(input);
    Tokenstruct *tokenList = NULL;
    int tokenCount = 0;
    int line = 1;

    while (right <= len && left <= right)
    {
        while(whiteSpace(input[right])){
            right++;
            left = right;
        }

        if(input[right] == '\n'){
            line++;
            right++;
            left = right;
        }

        if(!isDelimiter(input[right])){
            right++;
        }

        if(isDelimiter(input[right]) && left == right){
            if(isOperation(input[right])){
                tokenList = realloc (tokenList, sizeof(Tokenstruct) * (tokenCount + 1));
                tokenList[tokenCount].type = OPERATOR;
                tokenList[tokenCount].lexeme = malloc(2);
                tokenList[tokenCount].lexeme[0] = (char)input[right];
                tokenList[tokenCount].lexeme[1] = '\0';
                tokenCount++;
            } 
            else if (specialCaseDelimiter(input[right]) && left == right){
                tokenList = realloc (tokenList, sizeof(Tokenstruct) * (tokenCount + 1));
                tokenList[tokenCount].type = DELIMITER;
                tokenList[tokenCount].lexeme = malloc(2);
                tokenList[tokenCount].lexeme[0] = (char)input[right];
                tokenList[tokenCount].lexeme[1] = '\0';
                tokenCount++;
            }

            right++;
            left = right;
        }
        else if (isDelimiter(input[right]) && left != right || (right == len && left != right)){
            char *sub = getSubstring(input, left, right-1);

            if(isKeyword(sub)){
                tokenList = realloc (tokenList, sizeof(Tokenstruct) * (tokenCount + 1));
                tokenList[tokenCount].type = KEYWORD;
                tokenList[tokenCount].lexeme = sub;
                tokenCount++;
            }
            else if (isInteger (sub)) {
                tokenList = realloc (tokenList, sizeof(Tokenstruct) * (tokenCount + 1));
                tokenList[tokenCount].type = INTEGER;
                tokenList[tokenCount].lexeme = sub;
                tokenCount++;
            }
            else if (validIdentitfier(sub) && !isDelimiter(input[right-1])){
                tokenList = realloc (tokenList, sizeof(Tokenstruct) * (tokenCount + 1));
                tokenList[tokenCount].type = IDENTIFIER;
                tokenList[tokenCount].lexeme = sub;
                tokenCount++;
            }
            else if (!validIdentitfier(sub) && !isDelimiter(input[right-1])){
                tokenList = realloc (tokenList, sizeof(Tokenstruct) * (tokenCount + 1));
                tokenList[tokenCount].type = UNIDENTIFIED;
                tokenList[tokenCount].lexeme = sub;
                tokenCount++;
            }
            left = right;
        }
    }

    for (int i = 0; i < tokenCount; i++) {
        printf("Type: %s, Lexeme: %s\n", tokenTypeToString(tokenList[i].type), tokenList[i].lexeme);
    }

    //for now I free here I will change this because i need the list later on
    for(int i = 0; i < tokenCount; i++){
        free(tokenList[i].lexeme);
    }
    free(tokenList);

    return 0;
}