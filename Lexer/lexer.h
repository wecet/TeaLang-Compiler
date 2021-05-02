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
        bool isSpaceState(unsigned int state);
        bool isNL(char argc);
        bool isExlamation(char argc);
        bool isPunct(char argc);
        bool isSpace(char argc);
        bool isQuotes(char argc);
        bool isBackSlash(char argc);
        bool isForwardSlash(char argc);
        bool isGreaterLess(char argc);
        bool isUnderscore(char argc);
        bool isFullstop(char argc);

    class lexer{

    public:

        lexer();
        virtual ~lexer();
        lexer(std::string tealang);

    private:

        std::string input;
        int cIndex;
        int linenum;    

    };

};

#endif
