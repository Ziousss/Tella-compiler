# TELLA Compiler

Welcome to the **TELLA Compiler**, a basic **C compiler written in C**.

This project is an educational compiler developed to improve my practical knowledge of the C language and to deepen my understanding of fundamental concepts such as **parsing**, and **semantic analysis**.  It also provides hands-on experience with the inner workings of a computer, including x86-64 assembly and low-level code generation.

---

## Overview

- **Source language:** C
- **Implementation language:** C
- **Build system:** CMake

---

## Goal

The goal of this compiler is to **analyze C source code**, **detect errors**, and eventually **translate it into machine code** so that it can be safely executed.

This project is primarily focused on learning compiler design concepts rather than providing a production-ready compiler.

---

## Current Progress

- Lexer  
- Parser  
- Semantic Analyzer  
- IR 
- Assembly code x86_64
- The compiler can now compile and create executable for very simple programs.

---

## Next Steps

Now that the tella compiler can compile simple programs, I will compile it with all the warnings to make it the safest possible.

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
./compiler /path/to/the/file
```

You can also use the test file given in the folder.
Write the code to try in the test.c file.

```bash
cd build
./compiler ../tests/test1.c
```