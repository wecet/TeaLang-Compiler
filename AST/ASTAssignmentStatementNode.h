#ifndef ASTASSIGNMENTSTATEMENTNODE
#define ASTASSIGNMENTSTATEMENTNODE

#include <string>
#include "ASTExpressionNode.h"
#include "ASTStatementNode.h"
#include "../Visitor/Visitor.h"

using namespace std;

class ASTAssignmentStatementNode : public ASTStatementNode{

    public:
        ASTIdentifierExpressionNode* identifier;
        ASTExpressionNode* assignmentExpression;

        ASTAssignmentStatementNode(ASTIdentifierExpressionNode*, ASTExpressionNode*)
        void accept(Visitor* v);
        
};

#endif