#include "../include/lexer/tokenizer.h"
#include "../include/lexer/charcheck.h"

Tokenstruct *lexicalAnalyzer(char *input){
    int right = 0, left = 0, tokencount = 0;
    int line = 1;
    Tokenstruct *tokenList = NULL;
    int len = strlen(input);
    while (right < len){
        
        if(whiteSpace(input[right])){
            right++;
            left = right;
            continue;
        }

        if (input[right] == '\n'){
            right++;
            left = right;
            line++;
            continue;
        }

        //Delimiter token
        if (right == left && right < len){
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
                
                tokencount++;
                left = right;
                continue;
            }

            //Operator token
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
                tokencount++;
                left = right;
                continue;
            }

            //String and Char literal token
            if (input[right] == '\'')
            {
                right++;
                int start = right;
                while (input[right] != '\'')
                {
                    right++;
                }
                tokenList = realloc(tokenList, sizeof(Tokenstruct)*(tokencount+1));
                char *sub = getSubstring(input,start,right-1);
                int sublen = strlen(sub);
                maketokenString(tokenList,tokencount,CHAR_LITERAL, sub,sublen, line);
                right++;
                left = right;
                tokencount++;
                continue;
            }
            
            if (input[right] == '\"')
            {
                right++;
                int start = right;
                while (input[right] != '\"')
                {
                    right++;
                }
                tokenList = realloc(tokenList, sizeof(Tokenstruct)*(tokencount+1));
                char *sub = getSubstring(input,start,right-1);
                int sublen = strlen(sub);
                maketokenString(tokenList,tokencount,STRING_LITERAL, sub,sublen, line);
                right++;
                left = right;
                tokencount++;
                continue;
            }

            right++;
        }
        else if (right != left) {
            char *sub = getSubstring(input, left, right);
            int sublen = strlen(sub);
            if (isKeyword(sub)){
                tokenList = realloc(tokenList, sizeof(Tokenstruct)*(tokencount+1));
                for (int i = 0; keywords[i].lexeme != NULL ; i++){
                    if (strcmp(sub, keywords[i].lexeme) == 0){
                        maketokenString(tokenList, tokencount, keywords[i].type, sub, sublen, line);
                        right = left + sublen;
                        left = right;
                        tokencount++;
                    }
                }
                continue;
                
            }
            right++;
        }
        
        




        
    }
    for (int i = 0; i < tokencount; i++){
        printf("%s, %s\n", tokenList[i].lexeme, tokenTypeToString(tokenList[i].type));
    }
    return tokenList;
}