#ifndef NODEANALYSER_H
#define NODEANALYSER_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "../include/parser/ast.h"
#include "struct.h"
#include "helperFuncAnalyser.h"
#include "mainHelper.h"

GlobalFunc *programAnalyser(ASTnode *program);
void funcDefAnalyser(ASTnode *funcDefAst, SemContext *context);
void blockAnalyser(ASTnode *blockAst, SemContext *context, bool new_scope);
void stmtAnalyser(ASTnode *stmtAst, SemContext *context);
SemanticType expressionAnalyser(ASTnode *expressionAst, SemContext *context);
void returnAnalyser(ASTnode *returnAst, SemContext *context);
SemanticType assignAnalyser(ASTnode *assignment, SemContext *context);
SemanticType funcCallAnalyser(ASTnode *funcCallAst, SemContext *context);
void ifAnalyser(ASTnode *ifStmtAst, SemContext *context);
SemanticType binaryExprAnalyser(ASTnode *binary, SemContext *context);
void whileAnalyser(ASTnode *whileAst, SemContext *context);
void forAnalyser(ASTnode *forAst, SemContext *context);
void arrayAssignAnalyser(ASTnode *arrayAssign, SemContext *context);
SemanticType arrLoadAnalyser(ASTnode *arrayAssign, SemContext *context);
void funcSignAnalyser(ASTnode *funcSign, SemContext *context);

#endif