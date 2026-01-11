cmake_minimum_required(VERSION 3.10)
project(small_c_compiler C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

file(GLOB SOURCES 
    "source/*.c" 
    "source/lexer/*.c" 
    "source/parser/*.c" 
    "source/parser/grammarRules/*.c" 
    "source/semanticAnalyser/*.c"
    "source/semanticAnalyser/nodeAnalyser/*.c")

add_executable(compiler ${SOURCES})

