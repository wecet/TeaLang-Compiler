#ifndef LEXER
#define LEXER 

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <tuple>
#include <regex>
#include <vector>


namespace lexer{

        //Variables
        extern std::regex letter;
        extern std::regex number;
        extern std::regex printable;

        //Boolean Functions 
        bool isLetter(char argc);
        bool isNumber(char argc);
        bool isPrintable(char argc);

        bool isPlus(char argc);
        bool isStar(char argc);
        bool isMinus(char argc);
        bool isEquals(char argc);
       
    class lexer{

    public:

        lexer();
        ~lexer();

    };

};

#endif
