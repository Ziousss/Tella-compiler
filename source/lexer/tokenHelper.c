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
        case TOK_MINUS:             return "MINUS";
        case TOK_MINUSEQ:           return "MINUSEQ";
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
        
        case TOK_COMMA:             return "COMMA"; 
        case TOK_SEMICOLON:         return "SEMICOLON";
        case TOK_DOUBLEPOINT:       return "DOOUBLEPOINT";
        case TOK_EXCLAMATION:       return "EXCLAMATION";
        case TOK_DOT:               return "DOT";
        case TOK_HASHTAG:           return "HASHTAG";
        case TOK_QUOTE:             return "QUOTE";
        
        case TOK_IF:                return "IF";
        case TOK_WHILE:             return "WHILE";
        case TOK_RETURN:            return "RETURN";
        case TOK_FUNC:              return "FUNC";
        case TOK_FOR:               return "FOR";
        case TOK_CASE:              return "CASE";
        case TOK_ELSE:              return "ELSE";
        case TOK_INCLUDE:           return "INCLUDE";
        case TOK_INCLUDE_NAME:      return "INCLUDE_NAME";
        case TOK_LOCAL_INCLUDE:     return "INCLUDE_LOCAL";
        
        case TOK_INT:               return "INT_TYPE";
        case TOK_CHAR:              return "CHAR_TYPE";
        case TOK_VOID:              return "VOID_TYPE";
        
        case TOK_TRUE:              return "TRUE";
        case TOK_FALSE:             return "FALSE";
        
        case TOK_EOF:               return "EOF";
        case TOK_ERROR:             return "ERROR";
        
        default:                    return "NOT NAMED YET";
    }
}

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

Keyword keywords[] = {
    {"if", TOK_IF},
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