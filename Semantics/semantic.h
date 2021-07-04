#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <map>
#include <vector>
#include <stack>

#include "../Parser/ast.h"

namespace visitor{

    class SScope{
        public:
            bool already_referenced(std::string);
            //Overloaded Function
            bool already_referenced(std::string, std::vector<parser::VAR_TYPE>);

            void declare(std::string, parser::VAR_TYPE, unsigned int);
            //Overloaded Function
            void declare(std::string, parser::VAR_TYPE, std::vector<parser::VAR_TYPE>, unsigned int);

            parser::VAR_TYPE type(std::string);
            parser::VAR_TYPE type(std::string, std::vector<parser::VAR_TYPE>);

            unsigned int line(std::string);
            unsigned int line(std::string, std::vector<parser::VAR_TYPE>);

            std::vector<std::pair<std::string, std::string>> list();

        private:
            std::map<std::string, std::pair<parser::VAR_TYPE, unsigned int>> vartable;

            std::multimap<std::string, std::tuple<parser::VAR_TYPE, std::vector<parser::VAR_TYPE>,unsigned int>> funtable;

    };

    class Analysis : Visitor{
        public:
            Analysis();
            //Overloaded Object
            Analysis(SScope*);
            //Deconstructor
            ~Analysis();

            void visit(parser::ASTProgramNode*) override;
            void visit(parser::ASTDeclarationNode*) override;
            void visit(parser::ASTAssignmentNode*) override;
            void visit(parser::ASTPrintNode*) override;
            void visit(parser::ASTReturnNode*) override;
            void visit(parser::ASTBlockNode*) override;
            void visit(parser::ASTIfNode*) override;
            void visit(parser::ASTWhileNode*) override;
            void visit(parser::ASTFunctionNode*) override;
            void visit(parser::ASTLiteralNode<int>*) override;
            void visit(parser::ASTLiteralNode<float>*) override;
            void visit(parser::ASTLiteralNode<bool>*) override;
            void visit(parser::ASTLiteralNode<std::string>*) override;
            void visit(parser::ASTBinaryNode*) override;
            void visit(parser::ASTIdentifierNode*) override;
            void visit(parser::ASTUnaryNode*) override;
            void visit(parser::ASTFunctionCallNode*) override;

        private:
            std::vector<SScope*> scopes;
            std::stack<parser::VAR_TYPE> funcs;

            parser::VAR_TYPE type;
            std::vector<std::pair<std::string, parser::VAR_TYPE>> params;

            bool ret(parser::ASTStatementNode*);
    };

    std::string stringtype(parser::VAR_TYPE);

}

#endif