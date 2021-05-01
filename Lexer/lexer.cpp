#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "lexer.h"

std::regex lexer::letter("[A-Za-z]");
std::regex lexer::number("[0-9]");
std::regex lexer::printable("[\\x20-\\x7E]");

lexer::lexer::lexer() = default;
lexer::lexer::~lexer() = default;

// -- Defining Expressions --
bool lexer::isLetter(char argc){

    std::string argv;
    argv.push_back(argc);
    return (std::regex_match(argv, letter));

}

bool lexer::isNumber(char argc){

    std::string argv;
    argv.push_back(argc);
    return (std::regex_match(argv, number));

}

bool lexer::isPrintable(char argc){

    std::string argv;
    argv.push_back(argc);
    return (std::regex_match(argv, printable));
    
}

//Arithmetic Symbols
bool lexer::isPlus(char argc){

    return argc == '+';
}

bool lexer::isStar(char argc){

    return argc == 'x';
}

bool lexer::isMinus(char argc){

    return argc == '-';
}

bool lexer::isEquals(char argc){

    return argc == '=';
}


