#include "../include/lexer/tokenizer.h"
#include "../include/preprocess/preprocess.h"

Tokenstruct *lexicalAnalyzer(PreResult pre){
    SourceChar *input = pre.data;
    size_t right = 0, left = 0, tokencount = 0, start = 0;
    Tokenstruct *tokenList = NULL;
    size_t len = pre.size;
    size_t capacity = 64;
    tokenList = malloc(sizeof(Tokenstruct) * capacity);

    while (right < len){
        if(whiteSpace(input[right].c)){
            right++;
            left = right;
            continue;
        }

        if(input[right].c == '/' && right+1 < len && input[right+1].c == '/'){
            while(right < len && input[right].c != '\n'){
                ++right;
            }
            if(right < len) right++;
            left = right; 
            continue;
        }

        if(input[right].c == '/' && right+1 < len && input[right+1].c == '*'){
            right += 2;
            while(right + 1 < len && !(input[right].c == '*' && input[right+1].c == '/')){
                ++right;
            }
            if(right + 1 < len) right += 2;
            left = right; 
            continue;
        }

        if (input[right].c == '\n'){
            right++;
            left = right;
            continue;
        }

        if (right == left && right < len){

            start = right;

            if (input[right].c == '.'){
                tokenList = reallocTokenList(tokenList, tokencount, &capacity);
                if(tokenList == NULL) return NULL;
                
                maketokenChar(tokenList, tokencount, TOK_DOT, '.', input[start].line, input[start].fileName);
                right++;
                left = right;
                tokencount++;
                continue;
            }

            //Delimiter token
            if(isDelimiter(input[right].c)){
                tokenList = reallocTokenList(tokenList, tokencount, &capacity);
                if(tokenList == NULL) return NULL;

                switch (input[right].c)
                {
                    case '|': 
                        if(right+1 < len && input[right+1].c == '|'){
                            maketokenString(tokenList, tokencount, TOK_OR, "||", input[start].line, input[start].fileName);
                            right++;
                            break;
                        }
                        else{
                            printf("The character '|' in file %s line %ld cannot stand alone, maybe you meant ||?\n", input[start].fileName, input[start].line);
                            break;
                        }
                    case '&':
                        if(right+1 < len && input[right+1].c == '&'){
                            maketokenString(tokenList, tokencount, TOK_AND, "&&", input[start].line, input[start].fileName);
                            right++;
                            break;
                        }
                        else{
                            printf("The character '&' in file %s line %ld cannot stand alone, maybe you meant &&?\n", input[start].fileName, input[start].line);
                            break;
                        }
                    case '#': maketokenChar(tokenList, tokencount, TOK_HASHTAG, input[right].c, input[start].line, input[start].fileName); break;
                    case ';': maketokenChar(tokenList, tokencount, TOK_SEMICOLON, input[right].c, input[start].line, input[start].fileName); break;
                    case ',': maketokenChar(tokenList, tokencount, TOK_COMMA, input[right].c, input[start].line, input[start].fileName);break;
                    case '(': maketokenChar(tokenList, tokencount, TOK_LPAREN, input[right].c, input[start].line, input[start].fileName);break;
                    case ')': maketokenChar(tokenList, tokencount, TOK_RPAREN, input[right].c, input[start].line, input[start].fileName);break;
                    case '{': maketokenChar(tokenList, tokencount, TOK_LBRACE, input[right].c, input[start].line, input[start].fileName);break;
                    case '}': maketokenChar(tokenList, tokencount, TOK_RBRACE, input[right].c, input[start].line, input[start].fileName);break;
                    case '[': maketokenChar(tokenList, tokencount, TOK_LSQRTBRAK, input[right].c, input[start].line, input[start].fileName);break;
                    case ']': maketokenChar(tokenList, tokencount, TOK_RSQRTBRAK, input[right].c, input[start].line, input[start].fileName);break;
                    case ':': maketokenChar(tokenList, tokencount, TOK_DOUBLEPOINT, input[right].c, input[start].line, input[start].fileName);break;
                    default: maketokenChar(tokenList, tokencount, TOK_UNIDENTIFIED, input[right].c, input[start].line, input[start].fileName);break;
                }
                right++;
                tokencount++;
                left = right;
                continue;
            }

            //Operator token
            if(isOperation(input[right].c)){
                tokenList = reallocTokenList(tokenList, tokencount, &capacity);
                if(tokenList == NULL) return NULL;

                switch(input[right].c){
                    case '>':
                        if (right+1 >= len || input[right+1].c != '=') {
                            maketokenChar(tokenList, tokencount, TOK_GR, input[right].c, input[start].line, input[start].fileName);
                        } else {
                            maketokenString(tokenList, tokencount, TOK_GREQ, ">=", input[start].line, input[start].fileName);
                            right++;
                        }
                        break;
                    case '<':
                        if (right+1 >= len || input[right+1].c != '=') {
                            maketokenChar(tokenList, tokencount, TOK_LESS, input[right].c, input[start].line, input[start].fileName);
                        } else {
                            maketokenString(tokenList, tokencount, TOK_LESSEQ, "<=", input[start].line, input[start].fileName);
                            right++;
                        }
                        break;
                    case '+':
                        if (right+1 < len && input[right+1].c == '=') {
                            maketokenString(tokenList, tokencount, TOK_PLUSEQ, "+=", input[start].line, input[start].fileName);
                            right++;
                        } else if(right+1 < len && input[right+1].c == '+') {
                            maketokenString(tokenList, tokencount, TOK_PLUSPLUS, "++", input[start].line, input[start].fileName);
                            right++;
                        } else {
                            maketokenChar(tokenList, tokencount, TOK_PLUS, input[right].c, input[start].line, input[start].fileName);
                        }
                        break;
                    case '-':
                        if (right+1 < len && input[right+1].c == '=') {
                            maketokenString(tokenList, tokencount, TOK_MINUSEQ, "-=", input[start].line, input[start].fileName);
                            right++;
                        } else if(right+1 < len && input[right+1].c == '-') {
                            maketokenString(tokenList, tokencount, TOK_MINUSMINUS, "--", input[start].line, input[start].fileName);
                            right++;
                        } else {
                            maketokenChar(tokenList, tokencount, TOK_MINUS, input[right].c, input[start].line, input[start].fileName);
                        }
                        break;
                    case '/': maketokenChar(tokenList, tokencount, TOK_SLASH, input[right].c, input[start].line, input[start].fileName); break;
                    case '*': maketokenChar(tokenList, tokencount, TOK_STAR, input[right].c, input[start].line, input[start].fileName); break;
                    case '=':
                        if(right+1 < len && input[right+1].c == '='){
                            maketokenString(tokenList, tokencount, TOK_EQEQ, "==", input[start].line, input[start].fileName);
                            right++;
                        } else {
                            maketokenChar(tokenList, tokencount, TOK_EQ, input[right].c, input[start].line, input[start].fileName);
                        }
                        break;
                    case '!':
                        if (right+1 < len && input[right+1].c == '=') {
                            maketokenString(tokenList, tokencount, TOK_UNEQ, "!=", input[start].line, input[start].fileName);
                            right++;
                        } else {
                            maketokenChar(tokenList, tokencount, TOK_EXCLAMATION, '!', input[start].line, input[start].fileName);
                        }
                        break;
                    default:
                        maketokenChar(tokenList, tokencount, TOK_UNIDENTIFIED, input[right].c, input[start].line, input[start].fileName);
                        break;
                }

                right++;
                tokencount++;
                left = right;
                continue;
            }

            //String and Char literal token
            if (input[right].c == '\'')
            {
                right++;
                start = right;
                if(input[right].c == '\\'){
                    ++right;
                } 

                while(right < len && input[right].c != '\''){
                    right++;
                }


                tokenList = reallocTokenList(tokenList, tokencount, &capacity);
                if(tokenList == NULL) return NULL;

                char *sub = getSubstring(input,start,right-1);
                bool isValid = isValidChar(sub);
                right++;

                if(!isValid){
                    printf("The char line %ld is not valid.\n", input[start].line);
                    freeTokenList(tokenList);
                    return NULL;
                }

                maketokenString(tokenList,tokencount,TOK_CHAR_LITERAL, sub, input[start].line, input[start].fileName);
                free(sub);
                
                left = right;
                tokencount++;
                continue;
            }

            if (isdigit(input[right].c)){
                start = right;
                while (isdigit(input[right].c) && right+1 < len)
                {
                    right++;
                }

                tokenList = reallocTokenList(tokenList, tokencount, &capacity);
                if(tokenList == NULL) return NULL;

                char *sub = getSubstring(input, start,right-1);
                maketokenString(tokenList, tokencount, TOK_INTEGER_LITERAL, sub, input[start].line, input[start].fileName);
                free(sub);

                left = right;
                tokencount++;
                continue;
            }

            if (input[right].c == '\"'){
                right++;
                start = right;
                while (input[right].c != '\"')
                {
                    if(input[right].c == '\n'){
                        printf("Missing second of quote on line %ld file %s, check for missing quote.\n", input[start].line, input[start].fileName);
                        return NULL;
                    }
                    right++;
                }
                
                char *sub= getSubstring(input,start,right-1);

                tokenList = reallocTokenList(tokenList, tokencount, &capacity);
                if(tokenList == NULL) return NULL;
                maketokenString(tokenList,tokencount++,TOK_STRING_LITERAL, sub, input[start].line, input[start].fileName);
                free(sub);

                right++;
                left = right;
                continue;
            }

            if (isalpha(input[right].c) || input[right].c == '_') {
                start = right;
                right++;

                while (isalnum(input[right].c) || input[right].c == '_'){
                    right++;
                }

                tokenList = reallocTokenList(tokenList, tokencount, &capacity);
                if(tokenList == NULL) return NULL;


                if(right + 1 < len && input[right].c == '.' && input[right+1].c == 'h'){
                    char *sub = getSubstring(input, start, right + 1);
                    maketokenString(tokenList, tokencount, TOK_INCLUDE_NAME, sub, input[start].line, input[start].fileName);
                    free(sub);
                    right = right + 2;
                    left = right;
                }
                else{
                    char *sub = getSubstring(input, start, right - 1);
                    Tokentype type = keyword_type(sub);
                    
                    if(type == TOK_CHAR){
                        if(right+1 < len && (input[right].c == '*' || input[right+1].c == '*')){
                            free(sub);
                            if(input[right].c == ' '){
                                right++;
                            }
                            sub = getSubstring(input, start, right);
                            maketokenString(tokenList, tokencount, TOK_STRING, sub, input[start].line, input[start].fileName);
                            free(sub);
                            tokencount++;
                            right++;
                            left = right;
                            continue;
                        }
                    } 
                    maketokenString(tokenList, tokencount, type, sub, input[start].line, input[start].fileName);
                    free(sub);
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
    
    tokenList[tokencount].type = TOK_EOF;
    tokenList[tokencount].line = input[start].line;
    tokenList[tokencount].fileName = strdup(input[start].fileName);
    tokencount++;
    
    return tokenList;
}