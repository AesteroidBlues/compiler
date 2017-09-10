#pragma once
#include "lexer.h"
#include "types.h"
#include "ast_node.h"
#include <vector>

class Parser
{
  public:
    void Consume(std::shared_ptr<Lexer> lexer);
    void Finalize();

  private:
    bool Accept(TokenType t);
    bool Expect(TokenType t);

    bool ParseFunc(bool expect);
    bool ParseStatement(bool expect);

    // Expressions
    bool ParseExpression(bool expect);
    bool ParseExOr(bool expect);
    bool ParseExAnd(bool expect);
    bool ParseExEquals(bool expect);
    bool ParseExConcat(bool expect);
    bool ParseExCompare(bool expect);
    bool ParseExAdd(bool expect);
    bool ParseExMul(bool expect);
    bool ParseExPrefix(bool expect);
    bool ParseExPostfix(bool expect);
    bool ParseTerm(bool expect);

    // Control flow
    bool ParseWhileLoop(bool expect);
    bool ParseForLoop(bool expect);
    bool ParseIf (bool expect);
    bool ParseVarDecl(bool expect);
    bool ParseReturn(bool expect);
    bool ParseBlock(bool expect);

    bool ParseConstant(bool expect);
    bool ParseParens(bool expect);
    bool ParseIndex(bool expect);
    bool ParseCall(bool expect);
    bool ParseList(bool expect);
    bool ParseMap(bool expect);
    bool ParseKeyValPair(bool expect);

    std::shared_ptr<ASTNode> m_programRoot;
    std::shared_ptr<ASTNode> m_currentNode;

    std::shared_ptr<Lexer> m_currentLexer;
    std::vector<std::shared_ptr<Lexer>> m_lexers;
};