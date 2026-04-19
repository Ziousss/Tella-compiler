# TELLA Compiler

Welcome to the **TELLA Compiler**, a basic **C compiler written in C**.

**TELLA** is a small educational **C compiler written in C**, created in the sole purpose of understanding and explore how a compiler really works.

This project focuses on building a compiler **from scratch**, with an emphasis on **low-level understanding**, including parsing, semantic analysis, intermediate representations, and **x86-64 assembly generation**.

---

## Overview

- **Source language:** C
- **Implementation language:** C
- **Target architecture:** x86-64  
- **Build system:** CMake

---

## Goal

The main objective of TELLA is to:

- Analyze C source code
- Detect syntax and semantic errors
- Generate correct low-level code (x86-64 assembly)
- Produce working executables via GCC to transform assembly to binary

This is **not a production compiler**, but a deep dive into how compilers actually work under the hood.

---

## Current Progress

- Preprocessor (for local files for now)
- Lexer  
- Parser  
- Semantic Analyzer  
- IR 
- x86_64 assembly

- Compiler itself compiles and work for simple programs.

---

## Features

- All kinds of loop/statement; while and for loops and if statements (no else if for now).
- Arithmetic (No priority rule yet tho ...)
- 2 built-in functions, tellaPutChar and tellaPrint, which behave like putchar and printf (without format string).
- Include statement allowed thanks to the preprocessor (Can only include the .c files for now).
- An early libc you can include.
- Fairly precise error messages indicating the file and line where the mistake is.

---

## Debug & Visualization Tools

As this is an educational tool at its core, I created several functions dedicated to printing to the terminal the different outputs from each big part of the compiler.

TELLA includes tools to inspect internal stages:

```bash
./compiler -help
./compiler -h
```
These commands allow you to inspect the behavior of:
- Preprocessor
- Tokens
- AST
- IR
- StackLayout
- Assembly output

---

## Architecture Pipeline

Source Code → Lexer → Parser → AST → Semantic Analysis → IR → Assembly → Binary (via GCC)

---

## Known Limitations

- No optimization passes
- Basic error reporting
- Limited subset of C

---

## Memory Safety

- No memory leaks or invalid memory accesses detected on the current test suite (Valgrind)

---

## Next Steps

Implementing my own simple libc version compiled through the tella compiler.

---

## Installation

Clone the repository and build the project using CMake:

```bash
git clone https://github.com/ziousss/tella-compiler
cd tella-compiler
mkdir build && cd build
cmake ..
make
```

---

## Test

To use this compiler,

```bash
cd build
make
./compiler /path/to/the/file /path/to/executable
```