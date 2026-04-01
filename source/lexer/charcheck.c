#include "../include/lexer/charcheck.h"
#include "../include/preprocess/preprocess.h"

bool isDelimiter (char chr) {
    return (chr == ',' || chr == ',' || chr == '.'
            || chr == ';' || chr == '%' || chr == '(' 
            || chr == ')' || chr == '[' || chr == ']'
            || chr == '{' || chr == '}' || chr == ':'
            || chr == '#' || chr == '|' || chr == '&');
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

    for (size_t i = 1; i < strlen(str); i++){
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
        {"auto", "for", "while", "if", "else", "char", "include",
          "int", "float", "double", "struct", "const", 
          "long", "break", "case", "do", "return", "static",
          "sizeof", "void", "unsigned", "continue", "true", "false"};
  
    for(size_t i = 0; i < sizeof(keyword)/sizeof(keyword[0]); i++){
        if (strcmp(str, keyword[i]) == 0){
            return true;
        }
    } 
    return false;
}

char* getSubstring(SourceChar *src, size_t start, size_t end)
{
    size_t len = end - start + 1;
    char *out = malloc(len + 1);

    for(size_t i = 0; i < len; i++){
        out[i] = src[start + i].c;
    }

    out[len] = '\0';
    return out;
}

bool whiteSpace(char chr){
    return (chr == ' ' || chr == '\t' || chr == '\r');
}