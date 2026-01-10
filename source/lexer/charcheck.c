#include "../include/lexer/charcheck.h"

bool isDelimiter (char chr) {
    return (chr == ',' || chr == ',' || chr == '.'
            || chr == ';' || chr == '%' || chr == '(' 
            || chr == ')' || chr == '[' || chr == ']'
            || chr == '{' || chr == '}' || chr == ':');
}

bool isOperation (char chr) {
    return (chr == '+' || chr == '-' || chr == '*' 
            || chr == '/' || chr == '<' || chr == '='
            || chr == '>' || chr == '!');
}

bool notAccepted (char chr) {
    return (chr == '@' || chr == '"' || chr == '#' 
            || chr == '?' || chr == '!' || chr == '}'
            || chr == ' ' || chr == '+' || chr == '-'
            || chr == '*' || chr == '/' || chr == ','
            || chr == ';' || chr == '%' || chr == '>'
            || chr == '<' || chr == '=' || chr == '('
            || chr == ')' || chr == '[' || chr == ']'
            || chr == '{' || chr == '.');
}

bool validIdentitfier (char *str) {
    if (!isalpha(str[0]) && !(str[0] == '_')){
        return false;
    }   

    for (int i = 1; i < strlen(str); i++){
        if (notAccepted(str[i])){
            return false;
        }
    }

    if (isKeyword(str)){
        return false;
    }

    return true;
}

bool isKeyword (char *str) {
    const char *keyword[] = 
        {"auto", "for", "while", "if", "else", "char", 
          "int", "float", "double", "struct", "const", 
          "long", "break", "case", "do", "return", "static",
          "sizeof", "void", "unsigned", "continue", "true", "false"};
  
    for(int i = 0; i < sizeof(keyword)/sizeof(keyword[0]); i++){
        if (strcmp(str, keyword[i]) == 0){
            return true;
        }
    } 
    return false;
}

char* getSubstring (char *str, int start, int end) {
    int length = strlen(str);
    int sublength = end - start + 1;
    char* subStr = (char*)malloc((sublength + 1) * sizeof(char));

    strncpy(subStr, str+start, sublength);
    subStr[sublength] = '\0';
    return subStr;
}

bool whiteSpace(char chr){
    return (chr == ' ' || chr == '\t' || chr == '\r');
}