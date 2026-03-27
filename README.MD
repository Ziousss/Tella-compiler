# TELLA Compiler

Welcome to the **TELLA Compiler**, a basic **C compiler written in C**.

This project is an educational compiler developed to improve my practical knowledge of the C language and to deepen my understanding of fundamental concepts such as **parsing** and **semantic analysis**.  It also provides hands-on experience with the inner workings of a computer, including x86-64 assembly and low-level code generation.

---

## Overview

- **Source language:** C
- **Implementation language:** C
- **Build system:** CMake

---

## Goal

The goal of this compiler is to **analyze C source code**, **detect errors**, and eventually **translate it into machine code** so that it can be safely executed.

This project is primarily focused on learning compiler design concepts rather than providing a production-ready compiler.

Implementations have also been added to help visualise how my compiler works. To see those commands, run ./compiler -j or ./compiler -help

---

## Current Progress

- Preprocesser (for local files for now)
- Lexer  
- Parser  
- Semantic Analyzer  
- IR 
- Assembly code x86_64

---

## Architecture Pipeline

Source Code → Lexer → Parser → AST → Semantic Analysis → IR → Assembly → Binary (GCC)

---

## Known Limitations

- < 1% memory leak on standard programs
- No optimization passes
- Basic error reporting

---

## Next Steps

Implementing my own simple libc verison compiled through the tella compiler.

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
./compiler /path/to/the/file /path/to/executable
```

You can also use the test file given in the "tests" folder.
Write your test code in a '.c' file.

```bash
cd build
./compiler ../tests/test1.c test
```