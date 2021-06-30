#include <utility>
#include <iostream>

#include "ast.h"

using namespace parser;

ASTProgramNode::ASTProgramNode(std::vector<ASTNode*> argc):
    argc(std::move(argc))
{}


