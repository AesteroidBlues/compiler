#include <iostream>
#include "ast_node.h"

ASTNode::ASTNode() 
{
    auto startToken = std::make_shared<Token>();
    startToken->Type = TokenType::PROGRAM_START;
    m_token = startToken;
}

ASTNode::ASTNode(std::shared_ptr<Token> token)
    : m_depth(0),
    m_token(token)
{ }

void ASTNode::AddChild(std::shared_ptr<ASTNode> node)
{
    node->SetDepth(m_depth + 1);
    m_children.push_back(node);
}

std::string ASTNode::ToString() 
{
    return std::to_string(m_token->Type);
}

void ASTNode::PrintAST(std::shared_ptr<ASTNode> root)
{
    if (root == nullptr)
        return;

    auto children = root->GetChildren();
    for (auto child = children.begin(); child != children.end(); ++child)
    {
        printf("%*s %s\n", 2 * (*child)->GetDepth(), "", (*child)->ToString().c_str());
        PrintAST(*child);
    }
}