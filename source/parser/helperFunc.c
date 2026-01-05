#include "../include/parser/helperFunc.h"

bool isTOKType(Tokentype type){
    if(type != TOK_INT && type != TOK_CHAR && type != TOK_VOID){
        return false;
    }
    return true;
}

