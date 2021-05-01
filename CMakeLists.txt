cmake_minimum_required(VERSION 3.3)
project(Compiler Theory and Practice)

set(SOURCE_FILES Compiler/compiler.cpp
                 Compiler/compiler.h
                 Lexer/lexer.cpp
                 Lexer/lexer.h
                 Lexer/token.cpp
                 Lexer/token.h
                 main.cpp)

add_executable(Compiler Theory and Practice $(SOURCE_FILES))