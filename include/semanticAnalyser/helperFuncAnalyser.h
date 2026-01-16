#ifndef HERLPERFUNCANALYSER_H
#define HERLPERFUNCANALYSER_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "struct.h"
#include "../include/parser/helperFunc.h"
#include "../include/lexer/tokenizer.h"

void push_scope(SemContext *context);
void pop_scope(SemContext *context);
void push_variables(SymbolNode *sym, SemContext *context);
SymbolNode *find_in_scope(char *name, SemContext *context);
SemanticType fromTokToSem(Tokentype type);
char *fromSemToString(SemanticType type);
bool isBool(Tokentype op);
bool isCalculus (Tokentype op);

#endif