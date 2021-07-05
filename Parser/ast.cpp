#include <utility>
#include <iostream>

#include "ast.h"

using namespace parser;

ASTProgramNode::ASTProgramNode(std::vector<ASTNode*> argc):
    argc(std::move(argc))
{}

ASTDeclarationNode::ASTDeclarationNode(VAR_TYPE argc, std::string id, ASTExprNode *node, unsigned int line):
    type(argc),
    id(std::move(id)),
    node(node),
    number(line)

{}

ASTAssignmentNode::ASTAssignmentNode(std::string id, ASTExprNode *node, unsigned int line):
    id(id),
    argc(node),
    number(line)

{}

ASTPrintNode::ASTPrintNode(ASTExprNode *node, unsigned int line):
    argc(node),
    number(line)

{}

ASTReturnNode::ASTReturnNode(ASTExprNode *node, unsigned int line):
    argc(node),
    number(line)

{}

ASTBlockNode::ASTBlockNode(std::vector<ASTStatementNode*> argc, unsigned int line):
    argc(argc),
    number(line)

{}

ASTIfNode::ASTIfNode(ASTExprNode* comparison, ASTBlockNode* ifindent, unsigned int line, ASTExprNode* elsecompare, ASTBlockNode* elseindent):
    comparison(comparison),
    ifblock(ifindent),
    number(line),
    elsecomparison(elsecompare),
    elseblock(elseindent)

{}

ASTWhileNode::ASTWhileNode(ASTExprNode *condition, ASTBlockNode *whileblock, unsigned int line):
    condition(condition),
    whileblock(whileblock),
    number(line)

{}

ASTFunctionNode::ASTFunctionNode(std::string type, std::vector<std::pair<std::string, VAR_TYPE>> params, VAR_TYPE functype, ASTBlockNode *funcblock, unsigned int line):
    type(std::move(type)),
    params(std::move(params)),
    functype(functype),
    funcblock(funcblock),
    number(line)
{
    this->signature = std::vector<VAR_TYPE>();
    for(auto params : this -> params){
        variables.push_back(params.first);
        signature.push_back(params.second);
    }
}

/*
    EXPRESSION NODES
                        */

ASTBinaryNode::ASTBinaryNode(std::string op, ASTExprNode *l, ASTExprNode *r, unsigned int line):
    op(op),
    left(l),
    right(r),
    number(line)

{}

ASTIdentifierNode::ASTIdentifierNode(std::string id, unsigned int line):
    id(id),
    number(line)

{}

ASTUnaryNode::ASTUnaryNode(std::string op, ASTExprNode *argc, unsigned int line):
    op(op),
    expression(argc),
    number(line)

{}

ASTFunctionCallNode::ASTFunctionCallNode(std::string id, std::vector<ASTExprNode*> params, unsigned int line):
    functype(std::move(id)),
    signature(std::move(params)),
    number(line)

{}

void ASTBinaryNode::accept(visitor::Visitor *visit){
    visit->visit(this);
}

namespace parser{

    template <>
    void ASTLiteralNode<int>::accept(visitor::Visitor *visit){
        visit->visit(this);
    }

    template <>
    void ASTLiteralNode<float>::accept(visitor::Visitor *visit){
        visit->visit(this);
    }

    template <>
    void ASTLiteralNode<bool>::accept(visitor::Visitor *visit){
        visit->visit(this);
    }

    template <>
    void ASTLiteralNode<std::string>::accept(visitor::Visitor *visit){
        visit->visit(this);
    }

}

void ASTIdentifierNode::accept(visitor::Visitor *visit){
    visit->visit(this);
}

void ASTUnaryNode::accept(visitor::Visitor *visit){
    visit->visit(this);
}

void ASTDeclarationNode::accept(visitor::Visitor *visit){
    visit->visit(this);
}

void ASTAssignmentNode::accept(visitor::Visitor *visit){
    visit->visit(this);
}

void ASTPrintNode::accept(visitor::Visitor *visit){
    visit->visit(this);
}

void ASTReturnNode::accept(visitor::Visitor *visit){
    visit->visit(this);
}

void ASTBlockNode::accept(visitor::Visitor *visit){
    visit->visit(this);
}

void ASTIfNode::accept(visitor::Visitor *visit){
    visit->visit(this);
}

void ASTWhileNode::accept(visitor::Visitor *visit){
    visit->visit(this);
}

void ASTFunctionCallNode::accept(visitor::Visitor *visit){
    visit->visit(this);
}

void ASTProgramNode::accept(visitor::Visitor *visit){
    visit->visit(this);
}








    
