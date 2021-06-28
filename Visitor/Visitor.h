#ifndef VISITOR_H
#define VISITOR_H

#include <string>

namespace parser{

    class ASTAssignmentNode;
    class ASTBlockNode;
    class ASTBinaryNode;
    class ASTDeclarationNode;
    class ASTFunctionNode;
    class ASTFunctionCallNode;
    class ASTIdentifierNode;
    class ASTIfNode;
    class ASTProgramNode;
    class ASTPrintNode;
    class ASTReturnNode;
    class ASTUnaryNode;
    class ASTWhileNode;

    template <typename T> class ASTLiteralNode;

}

namespace visitor{

    class visitor{
        public: 
            
        virtual void visit(parser::ASTProgramNode*) = 0;
        virtual void visit(parser::ASTDeclarationNode*) = 0;
        virtual void visit(parser::ASTAssignmentNode*) = 0;
        virtual void visit(parser::ASTPrintNode*) = 0;
        virtual void visit(parser::ASTReturnNode*) = 0;
        virtual void visit(parser::ASTBlockNode*) = 0;
        virtual void visit(parser::ASTIfNode*) = 0;
        virtual void visit(parser::ASTWhileNode*) = 0;
        virtual void visit(parser::ASTFunctionNode*) = 0;
        virtual void visit(parser::ASTLiteralNode<int>*) = 0;
        virtual void visit(parser::ASTLiteralNode<float>*) = 0;
        virtual void visit(parser::ASTLiteralNode<bool>*) = 0;
        virtual void visit(parser::ASTLiteralNode<std::string>*) = 0;
        virtual void visit(parser::ASTBinaryNode*) = 0;
        virtual void visit(parser::ASTIdentifierNode*) = 0;
        virtual void visit(parser::ASTUnaryNode*) = 0;
        virtual void visit(parser::ASTFunctionCallNode*) = 0;
    };
}

#endif