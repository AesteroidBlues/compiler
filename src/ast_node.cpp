#include "ast_node.h"

ASTNode::ASTNode(std::shared_ptr<Token> token)
{
    
}

void ASTNode::AddChild(std::shared_ptr<ASTNode> node)
{
    m_children.push_back(node);
}