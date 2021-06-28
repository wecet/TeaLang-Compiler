#ifndef LEXER
#define LEXER 

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <tuple>
#include <regex>
#include <vector>

#include "token.h"


namespace lexer{

        //Variables
        extern std::regex letter;
        extern std::regex number;
        extern std::regex printable;

        enum TransitionType{
            
            LETTER = 0,
            NUMBER = 1,
            PRINTABLE = 2,
            PLUS = 6,
            STAR = 5,
            MINUS = 8,
            EQUALS = 14,
            FULLSTOP = 3,
            UNDERSCORE = 4,
            RELATIONAL = 7,
            FORWARDSLASH = 9,
            BACKSLASH = 10,
            QUOTES = 12,
            SPACE = 18,
            PUNCTUATION = 11,
            EXLAMATION = 15,
            NEWLINE = 13,
            INVALID = 17
        };

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

        std::vector<token> tealang_tokens;
        token getNextToken();
        token getLookahead();

        unsigned int position;

    class lexer{

    public:

        lexer();
        virtual ~lexer();
        lexer(std::string tealang);

        static TransitionType setTransitionType(char argc);

    private:

        std::string input;
        int cIndex;
        int linenum;    

    };

};

#endif