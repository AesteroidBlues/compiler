#pragma once
#include <vector>
#include "types.h"

class ASTNode
{
public:
    ASTNode(std::shared_ptr<Token> token);
    void AddChild(std::shared_ptr<ASTNode> node);
    
private:
    std::vector<std::shared_ptr<ASTNode>> m_children;
};