cmake_minimum_required(VERSION 3.10)
project(tella-compiler)

set(CMAKE_C_STANDARD 11)

include_directories(include)

file(GLOB SOURCES 
    "source/*.c" 
    "source/lexer/*.c" 
    "source/parser/*.c" 
    "source/parser/grammarRules/*.c" 
    "source/semanticAnalyser/*.c" 
    "source/semanticAnalyser/nodeAnalyser/*.c"
    "source/IntermediateRep/*.c"
    "source/IntermediateRep/IR/*.c"
    "source/assemblyInstr/Instr/*.c"
    "source/assemblyInstr/*.c")

add_executable(compiler ${SOURCES})

