#include <utility>
#include <iostream>

#include "ast.h"

using namespace parser;

ASTProgramNode::ASTProgramNode(std::vector<ASTNode*> argc):
    argc(std::move(argc))
{}

ASTDeclarationNode::ASTDeclarationNode(VAR_TYPE argc, std::string id, ASTExprNode *node, unsigned int line):
    type(argc),
    id(std::move(id))

{}
    
