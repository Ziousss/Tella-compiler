#include "../include/mainHelper.h"

MainContext *contextInit(char **argv, int argc){
    MainContext *context = malloc(sizeof(MainContext));
    if(context == NULL){
        printf("Malloc failed for Context int contextInit.\n");
        return NULL;
    }

    context->lexer = false;
    context->IR = false;
    context->parser = false;
    context->source = false;
    context->postSource = false;
    context->assembly = false;
    context->errors = 0;

    for(int i = 3; i < argc; i++){
        if(strcmp(argv[i], "-PR") == 0){
            context->postSource = true;
            continue;
        }
        else if(strcmp(argv[i], "-S") == 0){
            context->source = true;
            continue;
        }
        else if(strcmp(argv[i], "-I") == 0){
            context->IR = true;
            continue;
        }
        else if(strcmp(argv[i], "-L") == 0){
            context->lexer = true;
            continue;
        }
        else if(strcmp(argv[i], "-PA") == 0){
            context->parser = true;
            continue;
        }
        else if(strcmp(argv[i], "-A") == 0){
            context->assembly = true;
            continue;
        }

        printf("Unknown command [%s]. Use compiler -h to have the list of available commands.\n", argv[i]);
        context->errors++;
        return context;
    }

    return context;
}

bool compileAssembly(const char *asmFile, const char *outputFile){
    char command[256];
    snprintf(command, sizeof(command), "gcc %s -o %s", asmFile, outputFile);
    
    int result = system(command);
    if(result != 0){
        printf("Compilation failed\n");
        return false;
    }
    return true;
}

void cleanup(ASTnode *programNode, GlobalFunc *functions, IRstruct *IR, MainContext *contextMain, Tokenstruct *tokenList){
    free(contextMain);
    if(programNode != NULL){
        freeASTNode(programNode->data.program_node.func_def);
        free(programNode);
    }
    if(tokenList != NULL){
        freeTokenList(tokenList);
    }
    if(functions != NULL) freeFunctions(functions);
    if(IR != NULL) freeIR(IR);
}

void freeFunctions(GlobalFunc *functions){
    GlobalFunc *current = functions;
    while(current != NULL){
        GlobalFunc *next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
}

void freeIR(IRstruct *IR){
    IRstruct *current = IR;
    while(current != NULL){
        IRstruct *next = current->next;
        free(current);
        current = next;
    }
}

void printLexer(Tokenstruct *tokenList){
    int i = 0;
    while(tokenList[i].type != TOK_EOF){
        printf("%s, %s\n", tokenList[i].lexeme, tokenTypeToString(tokenList[i].type));
        i++;
    }
    printf("%s, %s\n", tokenList[i].lexeme, tokenTypeToString(tokenList[i].type));
}

void freeASTNode(ASTnode *node){
    if(node == NULL){
        return;
    }

    NodeType type = node->ast_type;
    switch (type) {
        case AST_FUNC_DEF:
        case AST_FUNC_DEF_MAIN: {
            free(node->data.func_def.name);
            freeASTNode(node->data.func_def.body);
            ParameterNode *param = node->data.func_def.parameters;
            if(param != NULL) {
                ParameterNode *current = param;
                while (current != NULL){
                    ParameterNode *next = current->next;
                    free(current->name);
                    free(current);
                    current = next;
                }
            }
            break;
        }
        case AST_ASSIGN_EXPR: {
            freeASTNode(node->data.assign.value);
            free(node->data.assign.target);
            break;
        }
        case AST_BINARY_EXPR:{
            freeASTNode(node->data.binary.left);
            freeASTNode(node->data.binary.right);
            break;
        }
        case AST_BLOCK: {
            freeASTNode(node->data.block.stmts);
            break;
        }
        case AST_BOOLEAN: 
        case AST_NUMBER:
        case AST_CHAR_LITERAL:{
            break;
        }
        
        case AST_FOR_STMT:{
            freeASTNode(node->data.for_node.block);
            freeASTNode(node->data.for_node.condition);
            freeASTNode(node->data.for_node.incrementation);
            freeASTNode(node->data.for_node.initialisation);
            break;
        }
        case AST_FUNC_CALL:{
            free(node->data.func_call.name);
            ArgNode *arg = node->data.func_call.args;
            ArgNode *current = arg;
            while(current != NULL){
                ArgNode *next = current->next;
                freeASTNode(current->expression);
                free(current);
                current = next;
            } 
            break;
        }
        case AST_IDENTIFIER:{
            free(node->data.identifier.name);
            break;
        }
        case AST_IF_STMT:{
            freeASTNode(node->data.if_node.condition);
            freeASTNode(node->data.if_node.else_branch);
            freeASTNode(node->data.if_node.if_branch);
            break;
        }
        
        case AST_RETURN:{
            freeASTNode(node->data.return_node.expr);
            break;
        }
        case AST_VAR_DECL:{
            freeASTNode(node->data.declaration.expression);
            break;
        }
        case AST_STRING_LITERAL:{
            free(node->data.string_literal.string);
            break;
        }
        case AST_WHILE_STMT:{
            freeASTNode(node->data.while_node.condition);
            freeASTNode(node->data.while_node.block);
            break;
        }
        case AST_ARRAY_DECL:{
            freeASTNode(node->data.arrayDecl.size);
            free(node->data.arrayDecl.name);
            break;
        }
        case AST_ASSIGN_ARRAY:{
            freeASTNode(node->data.arrayAssign.index);
            freeASTNode(node->data.arrayAssign.value);
            free(node->data.arrayAssign.name);
            break;
        }
        case AST_ARRAY_LOAD:{
            freeASTNode(node->data.arrayLoad.index);
            break;
        }

        default:{
            printf("Unknown ast type in freeASTNode.\n");
            break;
        }
    }

    if(node->next != NULL) {
        freeASTNode(node->next);
    }

    free(node);
}

void print_ast(ASTnode *node, int indent) {
    if (!node) {
        return;
    }

    for (int i = 0; i < indent; i++) printf("  ");

    printf("%s", astTypeToString(node->ast_type));

    // print value depending on type
    switch (node->ast_type) {
        case AST_IDENTIFIER:
            printf(" (name: %s)", node->data.identifier.name);
            break;

        case AST_NUMBER:
            printf(" (value: %d)", node->data.int_literal.value);
            break;

        case AST_STRING_LITERAL:
            printf(" (string: \"%s\")", node->data.string_literal.string);
            break;

        case AST_CHAR_LITERAL:
            printf(" (char: '%c')", node->data.character_literal.character);
            break;

        case AST_BOOLEAN:
            printf(" (bool: %s)", node->data.boolean_literal.boolean ? "true" : "false");
            break;

        case AST_FUNC_CALL:
            printf(" (call: %s)", node->data.func_call.name);
            break;

        case AST_FUNC_DEF:
        case AST_FUNC_DEF_MAIN:
            printf(" (func: %s)", node->data.func_def.name);
            break;

        /*
        case AST_INCLUDE:
            printf(" (include: %s)", node->data.include_node.name);
            break;
        */

        case AST_ASSIGN_EXPR:
            printf(" (assign to: %s)", node->data.assign.target);
            break;

        case AST_ASSIGN_ARRAY:
            printf(" (array assign to: %s)", node->data.arrayAssign.name);
            break;

        case AST_VAR_DECL:
            printf(" (var: %s)", node->data.declaration.identifier);
            break;

        case AST_ARRAY_DECL:
            printf(" (array: %s)", node->data.arrayDecl.name);
            break;
        
        case AST_ARRAY_LOAD:
            printf(" (Load: %s)", node->data.arrayLoad.name);
            break;

        default:
            break;
    }

    printf("\n");

    // recurse into children
    switch (node->ast_type) {
        case AST_BINARY_EXPR:
            print_ast(node->data.binary.left, indent + 1);
            print_ast(node->data.binary.right, indent + 1);
            break;

        case AST_ASSIGN_EXPR:
            print_ast(node->data.assign.value, indent + 1);
            break;

        case AST_ARRAY_DECL:
            print_ast(node->data.arrayDecl.size, indent + 1);
            break;

        case AST_VAR_DECL:
            print_ast(node->data.declaration.expression, indent + 1);
            break;

        case AST_ASSIGN_ARRAY:
            print_ast(node->data.arrayAssign.index, indent + 1);
            print_ast(node->data.arrayAssign.value,indent + 1);
            break;

        case AST_ARRAY_LOAD:
            print_ast(node->data.arrayLoad.index, indent + 1);
            break;

        case AST_FUNC_CALL: {
            ArgNode *arg = node->data.func_call.args;
            while (arg) {
                print_ast(arg->expression, indent + 1);
                arg = arg->next;
            }
            break;
        }

        case AST_BLOCK:
            print_ast(node->data.block.stmts, indent + 1);
            break;

        case AST_RETURN:
            print_ast(node->data.return_node.expr, indent + 1);
            break;

        case AST_IF_STMT:
            print_ast(node->data.if_node.condition, indent + 1);
            print_ast(node->data.if_node.if_branch, indent + 1);
            print_ast(node->data.if_node.else_branch, indent + 1);
            break;

        case AST_WHILE_STMT:
            print_ast(node->data.while_node.condition, indent + 1);
            print_ast(node->data.while_node.block, indent + 1);
            break;

        case AST_FOR_STMT:
            print_ast(node->data.for_node.initialisation, indent + 1);
            print_ast(node->data.for_node.condition, indent + 1);
            print_ast(node->data.for_node.incrementation, indent + 1);
            print_ast(node->data.for_node.block, indent + 1);
            break;

        case AST_FUNC_DEF:
        case AST_FUNC_DEF_MAIN:
            print_ast(node->data.func_def.body, indent + 1);
            break;

        case AST_PROGRAM:
            print_ast(node->data.program_node.func_def, indent + 1);
            break;

        default:
            break;
    }

    // move to next node in list
    print_ast(node->next, indent);
}