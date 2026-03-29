#include "../include/lexer/tokenizer.h"
#include "../include/lexer/charcheck.h"

Tokenstruct *lexicalAnalyzer(char *input){
    size_t right = 0, left = 0, tokencount = 0;
    int line = 1;
    Tokenstruct *tokenList = NULL;
    size_t len = strlen(input);
    size_t capacity = 16;
    tokenList = malloc(sizeof(Tokenstruct) * capacity);

    while (right < len){
        if(whiteSpace(input[right])){
            right++;
            left = right;
            continue;
        }

        if(input[right] == '/' && right+1 < len && input[right+1] == '/'){
            while(input[right] != '\n'){
                ++right;
            }
            ++right;
            ++line;
            left = right; 
            continue;
        }

        if(input[right] == '/' && right+1 < len && input[right+1] == '*'){
            while(input[right] != '*' || input[right+1] != '/'){
                if(input[right] == '\n'){
                    ++line;
                }
                ++right;
            }
            right+=2;
            left = right; 
            continue;
        }

        if (input[right] == '\n'){
            right++;
            left = right;
            line++;
            continue;
        }

        if (right == left && right < len){
            if (input[right] == '.'){
                tokenList = reallocTokenList(tokenList, tokencount, &capacity);
                if(tokenList == NULL) return NULL;
                
                maketokenChar(tokenList, tokencount, TOK_DOT, '.', 1, line);
                right++;
                left = right;
                tokencount++;
                continue;
            }

            //Delimiter token
            if(isDelimiter(input[right])){
                tokenList = reallocTokenList(tokenList, tokencount, &capacity);
                if(tokenList == NULL) return NULL;

                switch (input[right])
                {
                    case '|': 
                        if(input[right+1] == '|'){
                            maketokenString(tokenList, tokencount, TOK_OR, "||", 2, line);
                            right++;
                            break;
                        }
                        else{
                            printf("The character '|' cannot stand alone, maybe you meant ||?\n");
                            break;
                        }
                    case '&':
                        if(input[right+1] == '&'){
                            maketokenString(tokenList, tokencount, TOK_AND, "&&", 2, line);
                            right++;
                            break;
                        }
                        else{
                            printf("The character '&' cannot stand alone, maybe you meant &&?\n");
                            break;
                        }
                    case '#': maketokenChar(tokenList, tokencount, TOK_HASHTAG, input[right], 1, line); break;
                    case ';': maketokenChar(tokenList, tokencount, TOK_SEMICOLON, input[right], 1, line); break;
                    case ',': maketokenChar(tokenList, tokencount, TOK_COMMA, input[right], 1, line);break;
                    case '(': maketokenChar(tokenList, tokencount, TOK_LPAREN, input[right], 1, line);break;
                    case ')': maketokenChar(tokenList, tokencount, TOK_RPAREN, input[right], 1, line);break;
                    case '{': maketokenChar(tokenList, tokencount, TOK_LBRACE, input[right], 1, line);break;
                    case '}': maketokenChar(tokenList, tokencount, TOK_RBRACE, input[right], 1, line);break;
                    case '[': maketokenChar(tokenList, tokencount, TOK_LSQRTBRAK, input[right], 1, line);break;
                    case ']': maketokenChar(tokenList, tokencount, TOK_RSQRTBRAK, input[right], 1, line);break;
                    case ':': maketokenChar(tokenList, tokencount, TOK_DOUBLEPOINT, input[right], 1, line);break;
                    default: maketokenChar(tokenList, tokencount, TOK_UNIDENTIFIED, input[right], 1, line);break;
                }
                right++;
                
                tokencount++;
                left = right;
                continue;
            }

            //Operator token
            if(isOperation(input[right])){
                tokenList = reallocTokenList(tokenList, tokencount, &capacity);
                if(tokenList == NULL) return NULL;


                switch (input[right])
                {
                    case '>':
                        if (right+1 >= len || input[right+1] != '=') {
                            maketokenChar(tokenList, tokencount, TOK_GR, input[right], 1, line); break;
                        } else {
                            maketokenString(tokenList, tokencount, TOK_GREQ, ">=", 2, line); 
                            right++;
                            break; 
                        }
                    case '<':
                        if (right+1 >= len || input[right+1] != '=') {
                            maketokenChar(tokenList, tokencount, TOK_LESS, input[right], 1, line); break;
                        } else {
                            maketokenString(tokenList, tokencount, TOK_LESSEQ, "<=", 2, line); 
                            right++;
                            break; 
                        }
                    case '+': 
                        if (right+1 >= len || input[right+1] == '=') {
                            
                            maketokenString(tokenList, tokencount, TOK_PLUSEQ, "+=", 2, line); 
                            right++;
                            break; 
                        } else if(right+1 >= len || input[right+1] == '+') {
                            maketokenString(tokenList, tokencount, TOK_PLUSPLUS, "++", 2, line); 
                            right++;
                            break; 
                        }
                        else {
                            maketokenChar(tokenList, tokencount, TOK_PLUS, input[right], 1, line); break;
                        }
                    case '-': 
                        if (right+1 >= len || input[right+1] == '=') {
                            maketokenString(tokenList, tokencount, TOK_MINUSEQ, "-=", 2, line); 
                            right++;
                            break; 
                        } 
                        else if(right+1 >= len || input[right+1] == '-'){
                            maketokenString(tokenList, tokencount, TOK_MINUSMINUS, "--", 2, line); 
                            right++;
                            break; 
                        }
                        else {
                            maketokenChar(tokenList, tokencount, TOK_MINUS, input[right], 1, line);break;
                        }
                    case '/': maketokenChar(tokenList, tokencount, TOK_SLASH, input[right], 1, line);break;
                    case '*': maketokenChar(tokenList, tokencount, TOK_STAR, input[right], 1, line);break;
                    case '=': 
                        if(right+1 < len && input[right+1] == '='){
                            maketokenString(tokenList, tokencount, TOK_EQEQ, "==", 2, line);
                            right++;             
                            break; 
                        }
                        else {
                            maketokenChar(tokenList, tokencount, TOK_EQ, input[right], 1, line);break;
                        }
                    case '!':
                        if (right+1 < len && input[right+1] == '=') {
                            maketokenString(tokenList, tokencount, TOK_UNEQ, "!=", 2, line);
                            right++;             
                            break; 
                        } else {
                            maketokenChar(tokenList,tokencount,TOK_EXCLAMATION, '!', 1, line);
                            break;
                        }

                    default: maketokenChar(tokenList, tokencount, TOK_UNIDENTIFIED, input[right], 1, line);break;
                    
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
                size_t start = right;
                if(input[right] == '\\'){
                    ++right;
                } 

                while(right < len && input[right] != '\''){
                    right++;
                }


                tokenList = reallocTokenList(tokenList, tokencount, &capacity);
                if(tokenList == NULL) return NULL;

                char *sub = getSubstring(input,start,right-1);
                size_t sublen = strlen(sub);
                bool isValid = isValidChar(sub);
                right++;

                if(!isValid){
                    printf("The char line %d is not valid.\n", line);
                    freeTokenList(tokenList);
                    return NULL;
                }

                maketokenString(tokenList,tokencount,TOK_CHAR_LITERAL, sub,sublen, line);
                left = right;
                tokencount++;
                continue;
            }

            if (isdigit(input[right])){
                size_t start = right;
                while (isdigit(input[right]) && right+1 < len)
                {
                    right++;
                }

                tokenList = reallocTokenList(tokenList, tokencount, &capacity);
                if(tokenList == NULL) return NULL;

                char *sub = getSubstring(input, start,right-1);
                size_t sublen = strlen(sub);
                maketokenString(tokenList, tokencount, TOK_INTEGER_LITERAL, sub, sublen,line);

                left = right;
                tokencount++;
                continue;
            }
            if (input[right] == '\"'){
                right++;
                size_t start = right;
                while (input[right] != '\"')
                {
                    if(input[right] == '\n'){
                        printf("Missing second of quote on this line, check for missing quote on line %d.\n", line);
                        break;
                    }
                    right++;
                }
                
                char *sub = getSubstring(input,start,right-1);
                size_t sublen = strlen(sub);

                tokenList = reallocTokenList(tokenList, tokencount, &capacity);
                if(tokenList == NULL) return NULL;
                maketokenString(tokenList,tokencount++,TOK_STRING_LITERAL, sub,sublen, line);
                    
                
                right++;
                left = right;
                continue;
            }
            if (isalpha(input[right]) || input[right] == '_') {
                size_t start = right;
                right++;

                while (isalnum(input[right]) || input[right] == '_'){
                    right++;
                }

                tokenList = reallocTokenList(tokenList, tokencount, &capacity);
                if(tokenList == NULL) return NULL;


                if(right + 1 < len && input[right] == '.' && input[right+1] == 'h'){
                    char *sub = getSubstring(input, start, right + 1);
                    size_t sublen = strlen(sub);
                    maketokenString(tokenList, tokencount, TOK_INCLUDE_NAME, sub, sublen, line);
                    right = right + 2;
                    left = right;
                }
                else{
                    char *sub = getSubstring(input, start, right - 1);
                    size_t sublen = strlen(sub);
                    Tokentype type = keyword_type(sub);
                    
                    if(type == TOK_CHAR){
                        if(right+1 < len && (input[right] == '*' || input[right+1] == '*')){
                            if(input[right] == ' '){
                                right++;
                            }
                            sub = getSubstring(input, start, right);
                            sublen = strlen(sub);
                            maketokenString(tokenList, tokencount, TOK_STRING, sub, sublen, line);
                            tokencount++;
                            right++;
                            left = right;
                            continue;
                        }
                    } 
                    maketokenString(tokenList, tokencount, type, sub, sublen, line);
                }

                tokencount++;
                left = right;
                continue;
            }
            right++;
        }
    }
    tokenList = reallocTokenList(tokenList, tokencount, &capacity);
    if(tokenList == NULL) return NULL;
    maketokenChar(tokenList,tokencount,TOK_EOF,' ',0,line);
    tokencount++;
    
    return tokenList;

}