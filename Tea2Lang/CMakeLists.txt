cmake_minimum_required(VERSION 3.8)
project(Compiler_Theory_and_Practice)

set(CMAKE_CXX_STANDARD 14)

add_executable(Compiler_Theory_and_Practice main.cpp
                                            Lexer/lexer.cpp Lexer/lexer.h
                                            Lexer/token.cpp Lexer/token.h
                                            Parser/parser.cpp Parser/parser.h
                                            Parser/ast.cpp Parser/ast.h
                                            Interpreter/interpreter.cpp Interpreter/interpreter.h
                                            Visitor/visitor.h Visitor xmlvisitor.cpp Visitor xmlvisitor.cpp
                                            Semantics/semantic.cpp Semantics/semantic.h)