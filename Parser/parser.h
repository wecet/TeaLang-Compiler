#ifndef PARSER
#define PARSER

#include <vector>

#include "../Lexer/lexer.h"
#include "ast.h"


namespace parser{
    class Parser{

        public:
            explicit Parser(lexer::Lexer*);
            Parser(lexer::Lexer*, unsigned int);
            ASTProgramNode* parse();
            ASTExprNode* parsexpr();

        private:
            lexer::Lexer* l1;
            lexer::token current;
            lexer::token next;

            void pop_token();

            /* -------------
            Setting Up Statement Nodes
            ---------------- */

            ASTStatementNode* parsestate();
            ASTDeclarationNode* parsedec();
            ASTAssignmentNode* parseass();
            ASTPrintNode* parseprint();
            ASTReturnNode* parseret();
            ASTBlockNode* parseblock();
            ASTIfNode* parseif();
            ASTWhileNode* parsewhile();
            ASTFunctionNode* parsefunction();

            /* ---------------
            Setting Up Expression Nodes
            ------------------- */
            ASTExprNode* parse_sing_expr();
            ASTExprNode* parseterm();
            ASTExprNode* parsefactor();
            ASTFunctionCallNode parsefunc();

            VAR_TYPE type(std::string&);
            std::vector<ASTExprNode*> *parseparams();
            std::pair<std::string, VAR_TYPE>* parsefparam();
    };
}

#endif