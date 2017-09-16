#pragma once
#include <vector>
#include "types.h"

class ASTNode
{
public:
  ASTNode();
  ASTNode(std::shared_ptr<Token> token);
  void AddChild(std::shared_ptr<ASTNode> node);

  std::vector<std::shared_ptr<ASTNode>> GetChildren() { return m_children; }
  void SetDepth(int depth) { m_depth = depth; }
  int GetDepth() { return m_depth; }
  std::string ToString();
  
  static void PrintAST(std::shared_ptr<ASTNode> root);

private:
  int m_depth;
  std::shared_ptr<Token> m_token;
  std::vector<std::shared_ptr<ASTNode>> m_children;
};