#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

namespace lexer{

    enum TOKEN{
        TOK_IntLiteral, TOK_FloatLiteral, TOK_AdditiveOp, TOK_MultiplicativeOp,
        TOK_Equals, TOK_RelOp, TOK_LangType, TOK_If, TOK_Else, TOK_While,
        TOK_Def, TOK_Return, TOK_Let, TOK_Var, TOK_Print, TOK_And, TOK_Or, TOK_Not,
        TOK_Boolean, TOK_Identifier, TOK_EOF, TOK_String, TOK_OpenScope,
        TOK_CloseScope, TOK_OpenParenthesis, TOK_CloseParenthesis, TOK_Delimeter,
        TOK_Colon, TOK_Comma, TOK_Comment, TOK_Semicolon, TOK_Error, TOK_AutoLiteral, TOK_CharLiteral
    };


    class token{

        public:

            token();
            token(int, std::string, unsigned int line = 0);
            TOKEN type;
            std::string lexeme;
            unsigned int number;

        private:
            TOKEN settype(int, std::string&);

    };
};

#endif