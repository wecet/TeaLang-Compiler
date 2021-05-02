#include "token.h"

Token::Token(){

}

Token::Token(TOKEN tok, string argc, unsigned int argv){
    tokentype = tok;
    lexeme = argc;
    number = argv;
}
