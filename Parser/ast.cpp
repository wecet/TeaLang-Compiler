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



    
