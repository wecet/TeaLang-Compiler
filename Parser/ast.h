#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include "../Visitor/visitor.h"

namespace parser{
    
    enum VAR_TYPE 
    {FLOAT, INT, BOOL, STRING};

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

    /* The Below Classes are all in the form 

        Class Signature,
        Parameter Setting

        Since the classes below are all inherited Nodes from the above */

    class ASTProgramNode : public ASTNode{
        public:

            //Creating Signature for ASTDeclarationNode Creation in CPP File  
            explicit ASTProgramNode(std::vector<ASTNode*>);
            std::vector<ASTNode*> argc;

            void accept(visitor::Visitor*) override;
    };

    class ASTDeclarationNode : public ASTStatementNode{
        public:

            //Creating Signature for ASTDeclarationNode Creation in CPP File        
            ASTDeclarationNode(VAR_TYPE, std::string, ASTExprNode*, unsigned int);

            VAR_TYPE type;
            std::string id;
            ASTExprNode *node;
            unsigned int number;

            void accept(visitor::Visitor*) override;
    };

    class ASTAssignmentNode : public ASTStatementNode{
        public:

            //Creating Signature for ASTDeclarationNode Creation in CPP File  
            ASTAssignmentNode(std::string, ASTExprNode*, unsigned int);

            std::string id;
            ASTExprNode *argc;
            unsigned int number;
            
            void accept(visitor::Visitor*) override;

    };

    class ASTPrintNode : public ASTStatementNode{
        public:

        //Creating Signature for ASTDeclarationNode Creation in CPP File  
        ASTPrintNode(ASTExprNode*, unsigned int);
        
        ASTExprNode *argc;
        unsigned int number;

        void accept(visitor::Visitor*) override;

    };

    class ASTReturnNode : public ASTStatementNode{
        public:

        //Creating Signature for ASTDeclarationNode Creation in CPP File  
        ASTReturnNode(ASTExprNode*, unsigned int);

        ASTExprNode *argc;
        unsigned int number;

        void accept(visitor::Visitor*) override;
    };

    class ASTBlockNode : public ASTStatementNode{
        public:

        //Creating Signature for ASTDeclarationNode Creation in CPP File  
        ASTBlockNode(std::vector<ASTStatementNode*>, unsigned int);

        std::vector<ASTStatementNode*> argc;
        unsigned int number;

        void accept(visitor::Visitor*) override;
    };

    class ASTIfNode : public ASTStatementNode{
        public:

        //Creating Signature for ASTDeclarationNode Creation in CPP File  
        ASTIfNode(ASTExprNode*, ASTBlockNode*, unsigned int, ASTExprNode*, ASTBlockNode* = nullptr);

        ASTExprNode *comparison;
        ASTBlockNode *ifblock;
        ASTExprNode *elsecomparison;
        ASTBlockNode *elseblock;
        unsigned int number;

        void accept(visitor::Visitor*) override;
    };

    class ASTWhileNode : public ASTStatementNode{
        public:

        //Creating Signature for ASTDeclarationNode Creation in CPP File  
        ASTWhileNode(ASTExprNode*, ASTBlockNode*, unsigned int);
        
        ASTExprNode *condition;
        ASTBlockNode *whileblock;
        unsigned int number;

        void accept(visitor::Visitor*) override;
    };

    class ASTFunctionNode : public ASTStatementNode{
        public:

        //Creating Signature for ASTDeclarationNode Creation in CPP File
        ASTFunctionNode(std::string, std::vector<std::pair<std::string, VAR_TYPE>>, VAR_TYPE, ASTBlockNode*, unsigned int);

        std::string type;
        std::vector<std::pair<std::string, VAR_TYPE>> params;
        std::vector<std::string> variables;
        std::vector<VAR_TYPE> signature;  

        VAR_TYPE functype;
        ASTBlockNode* funcblock;

        unsigned int number;

        void accept(visitor::Visitor*) override;
    };

    // Expr Nodes
    template<typename T>

    class ASTLiteralNode : public ASTExprNode{

        public:
            ASTLiteralNode(T vartype, unsigned int number) : vartype(vartype), number(number) {};

            T vartype;
            unsigned int number;

            void accept(visitor::Visitor*) override;
    };

    class ASTBinaryNode : public ASTExprNode{
        public:
            ASTBinaryNode(std::string, ASTExprNode*, ASTExprNode*, unsigned int);

            std::string op;
            ASTExprNode *left;
            ASTExprNode *right;

            unsigned int number;
            
            void accept(visitor::Visitor*) override;
    };

    class ASTIdentifierNode : public ASTExprNode{
        public:
            ASTIdentifierNode(std::string, unsigned int);

            std::string id;
            unsigned int number;

            void accept(visitor::Visitor*) override;
    };

    class ASTUnaryNode : public ASTExprNode{
        public:
            ASTUnaryNode(std::string, ASTExprNode*, unsigned int);

            std::string op;
            ASTExprNode *expression;
            unsigned int number;

            void accept(visitor::Visitor*) override;
    };

    class ASTFunctionCallNode : public ASTExprNode{
        public:
            ASTFunctionCallNode(std::string, std::vector<ASTExprNode*>, unsigned int);

            std::string functype;
            std::vector<ASTExprNode*> signature;
            unsigned int number;

            void accept(visitor::Visitor*) override;
    };


}

#endif