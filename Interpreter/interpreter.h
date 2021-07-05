#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <map>
#include <stack>
#include "../Visitor/visitor.h"
#include "../Parser/ast.h"

namespace visitor{

    typedef struct VISITOR{
        VISITOR() : i(0), f(0), b(0), s("") {};

        int i;
        float f;
        bool b;
        std::string s;

    } variable;

    class IScope{

        bool already_referenced(std::string);
        //Overloaded Function
        bool already_referenced(std::string, std::vector<parser::VAR_TYPE>);

        void declare(std::string, int);
        void declare(std::string, float);
        void declare(std::string, bool);
        void declare(std::string, std::string);
        void declare(std::string, std::vector<parser::VAR_TYPE>, std::vector<std::string>, parser::ASTBlockNode*);

        parser::VAR_TYPE vartype_of(std::string);
        variable content(std::string);
        std::vector<std::string> names(std::string, std::vector<parser::VAR_TYPE>);
        parser::ASTBlockNode* block(std::string, std::vector<parser::VAR_TYPE>);

        std::vector<std::tuple<std::string, std::string, std::string>> varlist();

    private:
        std::map<std::string, std::pair<parser::VAR_TYPE, variable>> vartable;
        std::multimap<std::string, std::tuple<std::vector<parser::VAR_TYPE>,std::vector<std::string>,parser::ASTBlockNode*>> functable;

    };

    class Interpreter : public Visitor{
        public:

            Interpreter();
            Interpreter(IScope*);
            ~Interpreter();

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

            std::pair<parser::VAR_TYPE, variable> expression;

        private:
            std::vector<IScope*> scopes;
            parser::VAR_TYPE expression_type;
            variable expression_content;
            std::vector<std::string> params;
            std::vector<std::pair<parser::VAR_TYPE, variable>> args;  
    };

    std::string stringtype(parser::VAR_TYPE);
}

#endif