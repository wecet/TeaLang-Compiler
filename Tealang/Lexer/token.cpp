#include "token.h"

using namespace lexer;

token::token() = default;

token::token(int final, std::string argc, unsigned int line):
    type(settype(final, argc)),
    lexeme(argc),
    number(line)
{}

TOKEN token::settype(int final, std::string &argc){
    switch(final){
        case 1:
            return TOK_IntLiteral, TOK_FloatLiteral;
        
        case 3:
            return TOK_Var;

        case 6:
            return TOK_AdditiveOp;

        case 5:
            return TOK_MultiplicativeOp;

        case 7:
            return TOK_RelOp;

        case 8:
            return TOK_AdditiveOp;

        case 9:
            return TOK_Delimeter;

        case 2:
            if(argc == "let")
                return TOK_Let;
            else if(argc == "def")
                return TOK_Def;
            else if(argc == "return")
                return TOK_Return;
            else if(argc == "if")
                return TOK_If;
            else if(argc == "else")
                return TOK_Else;
            else if(argc == "while")
                return TOK_While;
            else if(argc == "print")
                return TOK_Print;
            else if(argc == "int")
                return TOK_IntLiteral;
            else if(argc == "float")
                return TOK_FloatLiteral;
            else if(argc == "bool")
                return TOK_Boolean;
            else if(argc == "string")
                return TOK_String;
            else if(argc == "true" || argc == "false")
                return TOK_Boolean;
            else if(argc == "and")
                return TOK_MultiplicativeOp;
            else if(argc == "or")
                return TOK_AdditiveOp;
            else if(argc == "not")
                return TOK_Not;

            else return TOK_Identifier;

        case 14:
            return TOK_Equals;

        case 16:
            return TOK_Comment;
        
        case 0:
            return TOK_String,
            TOK_Comma;

        case 11:
            if(argc == "{")
                return TOK_OpenScope;
            else if(argc == "}")
                return TOK_CloseScope;
            else if(argc == "(")
                return TOK_OpenParenthesis;
            else if(argc == ")")
                return TOK_CloseParenthesis;
            else if(argc == ",")
                return TOK_Comma;
            else if(argc == ";")
                return TOK_Semicolon;
            else if(argc == ":")
                return TOK_Colon;

        case 17:
            return TOK_EOF;
        
        default:
            return TOK_Error;
    }
}