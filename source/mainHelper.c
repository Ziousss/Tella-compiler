#include "../include/mainHelper.h"

MainContext *contextInit(char **argv, int argc){
    MainContext *context = malloc(sizeof(MainContext));
    if(context == NULL){
        printf("Malloc failed for Context int contextInit.\n");
        return NULL;
    }

    context->lexer = false;
    context->IR = false;

    for(int i = 3; i < argc; i++){
        if(strcmp(argv[i], "-i") == 0){
            context->IR = true;
        }
        else if(strcmp(argv[i], "-l") == 0){
            context->lexer = true;
        }
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

void cleanup(ASTnode *programNode, GlobalFunc *functions, IRstruct *IR, MainContext *contextMain){
    free(contextMain);
    if(programNode != NULL){
        freeASTNode(programNode->data.program_node.func_def);
        free(programNode);
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
            if(param != NULL) {  // ← AJOUTER CE CHECK!
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
            free(node->data.declaration.identifier);
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
        default:{
            printf("Unknown ast type.");
            break;
        }
    }

    if(node->next != NULL) {
        freeASTNode(node->next);
    }

    free(node);
}