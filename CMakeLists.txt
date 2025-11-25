cmake_minimum_required(VERSION 3.10)
project(small_c_compiler C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

# include all C files in source/ and source/lexer/
file(GLOB SOURCES "source/*.c" "source/lexer/*.c")

add_executable(compiler ${SOURCES})

