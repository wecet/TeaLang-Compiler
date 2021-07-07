#ifndef XML_H
#define XML_H

#include <fstream>
#include "visitor.h"
#include "../Parser/ast.h"

namespace visitor{

    class XML : public Visitor{

        public:
            //Constructor and Deconstructor
            XML();
            ~XML();

            //Visitors for AST Nodes
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
            std::ofstream xml;
            unsigned int indent;
            const std::string TAB = "    "; //4 Spaces
            std::string indenter();
            std::string string_var(parser::VAR_TYPE);
            std::string xmloperator(std::string);
    };

}
#endif