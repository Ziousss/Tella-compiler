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
SymbolNode *find_in_current_scope(char *name, SemContext *context);
SemanticType fromTokToSem(Tokentype type);
const char *fromSemToString(SemanticType type);
bool isBool(Tokentype op);
bool isCalculus (Tokentype op);
GlobalFunc *getAllFunctions(const SemContext *context);
Tokentype  fromSemToTok(SemanticType type);
IRsymbole *newIRsym(char *name, SemanticType type, int size, char *stringLit);
void pushIRSym(IRsymbole *symIR, SemContext *context);
int compSizeTInt(SemanticType type1, SemanticType type2);
bool canConvert(SemanticType target, SemanticType source, ASTnode *expr);

#endif