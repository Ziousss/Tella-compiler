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

        if(input[right] == '/' && right+1 < len && input[right+1] == '/'){
            while(input[right] != '\n'){
                ++right;
            }

            left == right; 
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
                tokenList = realloc(tokenList, sizeof(Tokenstruct)*(tokencount+1));
                maketokenChar(tokenList, tokencount, TOK_DOT, '.', 1, line);
                right++;
                left = right;
                tokencount++;
                continue;
            }

            //Delimiter token
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
                    default: maketokenChar(tokenList, tokencount, TOK_UNIDENTIFIED, input[right], 1, line);break;
                }
                right++;
                
                tokencount++;
                left = right;
                continue;
            }

            //Operator token
            //need to add <, > <=, >=
            if(isOperation(input[right])){
                printf("%c\n", input[right]);
                tokenList = realloc(tokenList, sizeof(Tokenstruct)*(tokencount+1));
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
                        if (right+1 >= len || input[right+1] != '=') {
                            maketokenChar(tokenList, tokencount, TOK_PLUS, input[right], 1, line); break;
                        } else {
                            maketokenString(tokenList, tokencount, TOK_PLUSEQ, "+=", 2, line); 
                            right++;
                            break; 
                        }
                    case '-': 
                    if (right+1 >= len || input[right+1] != '=') {
                            maketokenChar(tokenList, tokencount, TOK_MINUS, input[right], 1, line);break;
                        } else {
                            maketokenString(tokenList, tokencount, TOK_MINUSEQ, "-=", 2, line); 
                            right++;
                            break; 
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
                int start = right;
                while (input[right] != '\'' && right+1 , len)
                {
                    right++;
                }
                tokenList = realloc(tokenList, sizeof(Tokenstruct)*(tokencount+1));
                char *sub = getSubstring(input,start,right-1);
                int sublen = strlen(sub);
                maketokenString(tokenList,tokencount,TOK_CHAR_LITERAL, sub,sublen, line);
                right++;
                left = right;
                tokencount++;
                continue;
            }

            if (isdigit(input[right])){
                int start = right;
                while (isdigit(input[right]) && right+1 < len)
                {
                    right++;
                }
                tokenList = realloc(tokenList, sizeof(Tokenstruct)*(tokencount+1));
                char *sub = getSubstring(input, start,right-1);
                int sublen = strlen(sub);
                maketokenString(tokenList, tokencount, TOK_INTEGER_LITERAL, sub, sublen,line);

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
                maketokenString(tokenList,tokencount,TOK_STRING_LITERAL, sub,sublen, line);
                right++;
                left = right;
                tokencount++;
                continue;
            }
            if (isalpha(input[right]) || input[right] == '_') {
                int start = right;
                right++;

                while (isalnum(input[right]) || input[right] == '_')
                    right++;

                char *sub = getSubstring(input, start, right - 1);
                int sublen = strlen(sub);
                tokenList = realloc(tokenList, sizeof(Tokenstruct) * (tokencount + 1)); 

                if(isKeyword(sub)){
                    Tokentype type = keyword_type(sub);
                    maketokenString(tokenList, tokencount, type, sub, sublen, line);
                }
                else {
                    maketokenString(tokenList, tokencount, TOK_IDENTIFIER, sub, sublen, line);
                }

                tokencount++;
                left = right;
                continue;
            }
            right++;
        }
    }
    tokenList = realloc(tokenList, sizeof(Tokenstruct)*(tokencount+1));
    maketokenChar(tokenList,tokencount,TOK_EOF,' ',0,line);
    tokencount++;

    for (int i = 0; i < tokencount; i++){
        printf("%s, %s\n", tokenList[i].lexeme, tokenTypeToString(tokenList[i].type));
    }
    return tokenList;
}