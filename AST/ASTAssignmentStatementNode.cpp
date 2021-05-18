#include "ASTAssignmentStatementNode.h"

ASTAssignmentStatementNode::ASTAssignmentStatementNode(ASTIdentifierExpressionNode* id, ASTExpressionNode* expr){
    identifier = id;
    expression = expr;
}

void ASTAssignmentExpressionNode::accept(Visitor *v){
    v->visit(this)
}