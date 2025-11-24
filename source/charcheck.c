#include "../include/charcheck.h"

bool isDelimiter (char chr) {
    return (chr == ' ' || chr == '+' || chr == '-'
            || chr == '*' || chr == '/' || chr == ','
            || chr == ';' || chr == '%' || chr == '>'
            || chr == '<' || chr == '=' || chr == '('
            || chr == ')' || chr == '[' || chr == ']'
            || chr == '{' || chr == '}');
}

bool isOperation (char chr) {
    return (chr == '+' || chr == '-' || chr == '*' || chr == '/' 
            || chr == '=' || chr == '>' || chr == '<');
}

bool validIdentitfier (char chr) {
    return (chr != '0' && chr != '1' && chr != '2' 
            && chr != '3' && chr != '4' && chr != '5' 
            && chr != '6' && chr != '7' && chr != '8' 
            && chr != '9' && !isDelimiter(chr));
}

bool isKeyword (char *str) {
    const char *keyword[] = 
        {"auto", "for", "while", "if", "else", "char", 
          "int", "float", "double", "struct", "const", 
          "long", "break", "case", "do", "return", "static",
          "sizeof", "void", "unsigned", "continue"};
  
    for(int i = 0; i < sizeof(keyword)/sizeof(keyword[0]); i++){
        if (strcmp(str, keyword[i]) == 0){
            return true;
        }

    return false;
    } 
}

bool isInteger (char *str) {
    if (str == NULL || *str == '\0'){
        return false;
    }

    int i = 0;
    while (isdigit(str[i])){
        i++;
    }

    return str[i] == '\0';
}

char* getSubstring (char *str, int start, int end) {
    int length = strlen(str);
    int sublength = end - start + 1;
    char* subStr = (char*)malloc((sublength + 1) * sizeof(char));

    strncpy(subStr, str+start, sublength);
    subStr[sublength] = '\0';
    return subStr;
}