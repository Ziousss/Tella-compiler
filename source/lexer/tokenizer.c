#include "../include/lexer/tokenizer.h"
#include "../include/lexer/charcheck.h"

Tokenstruct *maketokenChar (Tokenstruct *tokenlist, int count, Tokentype type, char chr, int length, int line){
    tokenlist[count].type = type;
    tokenlist[count].lexeme = malloc(2);
    tokenlist[count].lexeme[0] = (char)chr;
    tokenlist[count].lexeme[1] = '\0';
    tokenlist[count].line = line;
    tokenlist[count].length = length;
    return tokenlist;
}

Tokenstruct *maketokenString (Tokenstruct *tokenlist, int count, Tokentype type, char *sub, int length, int line) {
    tokenlist[count].type = type;
    tokenlist[count].lexeme = sub;
    tokenlist[count].line = line;
    tokenlist[count].length = length;
    return tokenlist;
}

Tokenstruct *lexicalAnalyzer(char *input){
    int right = 0, left = 0, tokencount = 0;
    int line = 1;
    Tokenstruct *tokenList = NULL;
    int len = strlen(input);
    while (right < len){

        if(isDelimiter(input[right])){
            tokenList = realloc(tokenList, sizeof(Tokenstruct)*(tokencount+1));
            switch (input[right])
            {
                case ';': maketokenChar(tokenList, tokencount, TOK_SEMICOLON, input[right], 1, line); break;
                case ',': maketokenChar(tokenList, tokencount, TOK_COMMA, input[right], 1, line);break;
                case '(': maketokenChar(tokenList, tokencount, TOK_LPAREN, input[right], 1, line);break;
                case ')': maketokenChar(tokenList, tokencount, TOK_RPAREN, input[right], 1, line);break;
                case '{': maketokenChar(tokenList, tokencount, TOK_LBRACE, input[right], 1, line);break;
                case '}': maketokenChar(tokenList, tokencount, TOK_RBRACE, input[right], 1, line);break;
                case '[': maketokenChar(tokenList, tokencount, TOK_LSQRTBRAK, input[right], 1, line);break;
                case ']': maketokenChar(tokenList, tokencount, TOK_RSQRTBRAK, input[right], 1, line);break;
                case ':': maketokenChar(tokenList, tokencount, TOK_DOUBLEPOINT, input[right], 1, line);break;
                default: maketokenChar(tokenList, tokencount, UNIDENTIFIED, input[right], 1, line);break;
            }
            right++;
            printf("%s", tokenList[tokencount].lexeme);
            tokencount++;
            left = right;
            continue;
        }
        //need to add <, > <=, >= and - 
        if(isOperation(input[right])){
            tokenList = realloc(tokenList, sizeof(Tokenstruct)*(tokencount+1));
            switch (input[right])
            {
                case '+': maketokenChar(tokenList, tokencount, TOK_PLUS, input[right], 1, line); break;
                case '-': maketokenChar(tokenList, tokencount, TOK_MINUS, input[right], 1, line);break;
                case '/': maketokenChar(tokenList, tokencount, TOK_SLASH, input[right], 1, line);break;
                case '*': maketokenChar(tokenList, tokencount, TOK_STAR, input[right], 1, line);break;
                case '=': 
                    if(input[right+1] == '='){
                        maketokenString(tokenList, tokencount, TOK_EQEQ, "==", 2, line);
                        right++;
                    } else {
                        maketokenChar(tokenList, tokencount, TOK_EQ, input[right], 1, line);break;
                    }
                
                default: maketokenChar(tokenList, tokencount, UNIDENTIFIED, input[right], 1, line);break;
            }
            right++;
            printf("%s", tokenList[tokencount].lexeme);
            tokencount++;
            left = right;
            continue;
        }

        

        right++;        








    }
    return tokenList;
}