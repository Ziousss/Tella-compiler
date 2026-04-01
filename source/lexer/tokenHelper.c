#include "../include/lexer/tokenizer.h"

const char* tokenTypeToString(int type) {
    switch (type) {
        case TOK_IDENTIFIER:        return "IDENTIFIER";
        case TOK_INTEGER_LITERAL:   return "INTEGER_LITERAL";
        case TOK_FLOAT_LITERAL:     return "FLOAT_LITERAL";
        case TOK_CHAR_LITERAL:      return "CHAR_LITERAL";
        case TOK_STRING_LITERAL:    return "STRING_LITERAL";
        case TOK_UNIDENTIFIED:      return "UNIDENTIFIED";

        case TOK_PLUS:              return "PLUS";
        case TOK_PLUSEQ:            return "PLUSEQ";
        case TOK_PLUSPLUS:          return "PLUSPLUS";
        case TOK_MINUS:             return "MINUS";
        case TOK_MINUSEQ:           return "MINUSEQ";
        case TOK_MINUSMINUS:        return "MINUSMINUS";
        case TOK_STAR:              return "STAR";
        case TOK_SLASH:             return "SLASH";
        case TOK_UNEQ:              return "UNEQ";
        case TOK_GREQ:              return "GREQ";
        case TOK_GR:                return "GR";
        case TOK_LESSEQ:            return "LESSEQ";
        case TOK_LESS:              return "LESS";
        
        case TOK_EQ:                return "EQUAL";
        case TOK_EQEQ:              return "EQUAL_EQUAL";
        
        case TOK_LPAREN:            return "LEFT_PAREN";
        case TOK_RPAREN:            return "RIGHT_PAREN";
        case TOK_LBRACE:            return "LEFT_BRACE";
        case TOK_RBRACE:            return "RIGHT_BRACE";
        case TOK_LSQRTBRAK:         return "LEFT_SQRTBRAK";
        case TOK_RSQRTBRAK:         return "RIGHT_SQRTBRAK";
        
        case TOK_COMMA:             return "COMMA"; 
        case TOK_SEMICOLON:         return "SEMICOLON";
        case TOK_DOUBLEPOINT:       return "DOOUBLEPOINT";
        case TOK_EXCLAMATION:       return "EXCLAMATION";
        case TOK_DOT:               return "DOT";
        case TOK_HASHTAG:           return "HASHTAG";
        case TOK_QUOTE:             return "QUOTE";
        
        case TOK_IF:                return "IF";
        case TOK_DEFINE:            return "DEFINE";
        case TOK_WHILE:             return "WHILE";
        case TOK_RETURN:            return "RETURN";
        case TOK_FUNC:              return "FUNC";
        case TOK_FOR:               return "FOR";
        case TOK_CASE:              return "CASE";
        case TOK_ELSE:              return "ELSE";
        case TOK_INCLUDE:           return "INCLUDE";
        case TOK_INCLUDE_NAME:      return "INCLUDE_NAME";
        case TOK_LOCAL_INCLUDE:     return "INCLUDE_LOCAL";
        case TOK_SIZET:             return "SIZE_T";
        
        case TOK_INT:               return "INT_TYPE";
        case TOK_CHAR:              return "CHAR_TYPE";
        case TOK_VOID:              return "VOID_TYPE";
        case TOK_STRING:            return "STRING_TYPE";
        
        case TOK_BOOL:              return "BOOL";
        case TOK_TRUE:              return "TRUE";
        case TOK_FALSE:             return "FALSE";
        case TOK_NULL:              return "NULL";
        case TOK_AND:               return "AND";
        case TOK_OR:                return "OR";
        
        case TOK_EOF:               return "EOF";
        case TOK_ERROR:             return "ERROR";
        
        default:                    return "NOT NAMED YET";
    }
}

Tokenstruct *maketokenChar (Tokenstruct *tokenlist, size_t count, Tokentype type, char chr, size_t length, size_t line, const char *fileName){
    tokenlist[count].type = type;
    char *temp = (char *)malloc(2);
    temp[0] = chr;
    temp[1] = '\0';
    tokenlist[count].lexeme = temp;
    tokenlist[count].line = line;
    tokenlist[count].length = length;
    tokenlist[count].fileName = fileName;
    return tokenlist;
}

Tokenstruct *maketokenString (Tokenstruct *tokenlist, size_t count, Tokentype type, const char *sub, size_t length, size_t line, const char *fileName) {
    tokenlist[count].type = type;
    char *string = strdup(sub);
    tokenlist[count].lexeme = string;
    tokenlist[count].line = line;
    tokenlist[count].length = length;
    tokenlist[count].fileName = fileName;
    return tokenlist;
}

const Keyword keywords[] = {
    {"if", TOK_IF},
    {"size_t", TOK_SIZET},
    {"else", TOK_ELSE},
    {"while", TOK_WHILE},
    {"for", TOK_FOR},
    {"do", TOK_DO},
    {"switch", TOK_SWITCH},
    {"case", TOK_CASE},
    {"break", TOK_BREAK},
    {"continue", TOK_CONTINUE},
    {"return", TOK_RETURN},
    {"int", TOK_INT},
    {"char", TOK_CHAR},
    {"include", TOK_INCLUDE},
    {"void", TOK_VOID},
    {"true", TOK_TRUE},
    {"false", TOK_FALSE},
    {"NULL", TOK_NULL},
    {"bool", TOK_BOOL},
    {"define", TOK_DEFINE},
    {NULL, 0} 
};

Tokentype keyword_type(char *sub){
    for (int i = 0; keywords[i].lexeme != NULL; i++){
        if (strcmp(keywords[i].lexeme, sub) == 0) {
            return keywords[i].type;
        }
    }
    return TOK_IDENTIFIER;
}

void freeTokenList(Tokenstruct *tokenlist){
    int i = 0;
    while(tokenlist[i].type != TOK_EOF) {
        if(tokenlist[i].lexeme != NULL) {
            free((void*)tokenlist[i].lexeme);
        }
        i++;
    }
    free(tokenlist);
}

Tokenstruct* reallocTokenList(Tokenstruct* list, size_t tokencount, size_t* capacity) {
    if(tokencount >= *capacity){
        *capacity *= 2;
        Tokenstruct* newList = realloc(list, sizeof(Tokenstruct) * (*capacity));
        if(!newList){ freeTokenList(list); printf("realloc failed"); return NULL; }
        return newList;
    }
    return list;
}

bool isValidChar(char *string){
    if(string == NULL) return false;
    
    size_t len = strlen(string);
    
    if(len == 1){
        return true;
    }
    
    if(len == 2 && string[0] == '\\'){
        char escape_char = string[1];
        return (escape_char == 'n' || 
                escape_char == 't' || 
                escape_char == 'r' || 
                escape_char == '0' || 
                escape_char == '\\' || 
                escape_char == '\'' || 
                escape_char == '"');
    }
    
    return false;
}