# CPT316-Simple-Compiler

A simple compiler implementation for MiniLang, featuring lexical analysis and syntax analysis with detailed error reporting.

## Objective
The main objective of this project is to implement a simple compiler for MiniLang, a simple programming language. The compiler is implemented in C++ and consists of a lexical analyzer, syntax analyzer, and error reporting. The compiler reads the input source code from a file, performs lexical analysis to generate tokens, and then performs syntax analysis to generate an abstract syntax tree (AST). The compiler also reports errors in the source code, such as lexical errors, and syntax errors.

## Features
- Lexical Analysis
- Syntax Analysis
- Abstract Syntax Tree (AST)
- Error Reporting

## Team Members
- [Koay Chun Keat](https://github.com/koayck)
- [Lai Yicheng](https://github.com/Jisi-A)
- [Lim Ting Juin](https://github.com/juin03)

## Usage

1. Run the compiler:
```bash
cd out/build/my\ preset
./CPT316-Simple-Compiler
```
2. When prompted, just enter the filename (e.g., `valid-test-1.txt`)

## Project Structure



```
CPT316-Simple-Compiler
├─ .gitignore
├─ CMakeLists.txt
├─ out
│  ├─ build
│  └─ my preset
│      └─ CPT316-Simple-Compiler.exe
├─ input
│  ├─ invalid-test-1.txt (lexical error)
│  ├─ invalid-test-2.txt (syntax error)
│  └─ valid-test-1.txt
├─ README.md
└─ src
   ├─ AST.h
   ├─ Lexer.cpp
   ├─ Lexer.h
   ├─ main.cpp
   ├─ Parser.cpp
   ├─ Parser.h
   └─ Token.h
```