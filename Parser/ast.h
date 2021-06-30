#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include "../Visitor/visitor.h"

namespace parser{
    
    enum VAR_TYPE 
    {INT, VAR, BOOL, STRING};

    class ASTNode{
        public:
            virtual void accept(visitor::Visitor*) = 0;
    };

    class ASTStatementNode : public ASTNode{
        public:
            void accept(visitor::Visitor*) override = 0;
    };

    class ASTExprNode : public ASTNode{
        public:
            void accept(visitor::Visitor*) override = 0;
    };

    class ASTProgramNode : public ASTNode{
        public:
            explicit ASTProgramNode(std::vector<ASTNode*>);
            std::vector<ASTNode*> argc;
            void accept(visitor::Visitor*) override;
    };
}

#endif