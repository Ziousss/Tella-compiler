#ifndef MAINHELPER_H
#define MAINHELPER_H

#include "../include/lexer/tokenizer.h"
#include "../include/lexer/readFile.h"
#include "../include/parser/grammarRules.h"
#include "../include/semanticAnalyser/nodeAnalyser.h"
#include "../include/IntermediateRep/IRheader.h"
#include "../include/assemblyInstr/assemblyInstrHeader.h"
#include <string.h>
#include <stdlib.h>

typedef struct {
    int errors;

    bool source;
    bool postSource;
    bool lexer;
    bool IR;
    bool parser;
    bool assembly;
    bool stackLayout;
} MainContext;

MainContext *contextInit(char **argv, int argc);
bool compileAssembly(const char *asmFile, const char *outputFile);
void cleanup(ASTnode *programNode, GlobalFunc *functions, IRstruct *IR, MainContext *contextMain, Tokenstruct *tokenList);
void freeFunctions(GlobalFunc *functions);
void freeIR(IRstruct *IR);
void printLexer(Tokenstruct *tokenList);
void freeASTNode(ASTnode *node);
void print_ast(ASTnode *node, int indent);
#endif