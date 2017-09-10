#include "parser.h"


void Parser::Consume(std::shared_ptr<Lexer> lex)
{
    m_lexers.push_back(lex);
}

void Parser::Finalize()
{
    m_currentLexer = m_lexers.back();
    while(ParseFunc(false))
    {
        m_lexers.pop_back();
        m_currentLexer = m_lexers.back();
    }
}

bool Parser::Accept(TokenType t)
{
    if (m_currentLexer->Current()->Type == t)
    {
        auto newNode = std::make_shared<ASTNode>(m_currentLexer->Current());
        m_currentNode->AddChild(newNode);
        m_currentNode = newNode;

        m_currentLexer->Advance();
        return true;
    }

    // Throw parse exception
    return false;
}

bool Parser::Expect(TokenType t)
{
    if (m_currentLexer->Current()->Type != t)
    {
        // Throw parse exception
        return false;
    }

    m_currentLexer->Advance();
    return true;
}

bool Parser::ParseFunc(bool expect)
{
    if(Accept(TokenType::K_FUNCTION))
    {
        Expect(TokenType::LPAREN);
        while (m_currentLexer->Current()->Type != TokenType::RPAREN)
        {
            auto paramNode = std::make_shared<ASTNode>(m_currentLexer->Current());
            m_currentNode->AddChild(paramNode);
            m_currentLexer->Advance();
        }

        // Open a scope on the LBrace
        Accept(TokenType::LBRACE);
        
        while (m_currentLexer->Current()->Type != TokenType::END)
        {
            ParseStatement(false);
        }

        return true;
    }

    return false;
}

bool Parser::ParseStatement(bool expect)
{
    if (ParseExpression(false))
    {
        Expect(TokenType::SEMI);
        return true;
    }

    if (ParseVarDecl(false))
    {
        Expect(TokenType::SEMI);
        return true;
    }

    if (ParseBlock(false) ||
        ParseWhileLoop(false) ||
        ParseForLoop(false) ||
        ParseIf(false) ||
        ParseReturn(false))
    {
        return true;
    }

    return false;
}

bool Parser::ParseExpression(bool expect)
{
    if (ParseExOr(false))
    {
        if (Accept(TokenType::OP_MUL_ASSIGN) ||
            Accept(TokenType::OP_DIV_ASSIGN) ||
            Accept(TokenType::OP_ADD_ASSIGN) ||
            Accept(TokenType::OP_SUB_ASSIGN) ||
            Accept(TokenType::OP_CONCAT_ASSIGN))
        {
            ParseExpression(true);
        }

        return true;
    }

    // if expect, throw parse error
    return false;
}

bool Parser::ParseExOr(bool expect)
{
    if (ParseExAnd(false))
    {
        if (Accept(TokenType::OP_OR))
        {
            ParseExOr(true);
        }

        return true;
    }

    return false;
}

bool Parser::ParseExAnd(bool expect)
{
    if (ParseExEquals(false))
    {
        if (Accept(TokenType::OP_AND))
        {
            ParseExAnd(true);
        }

        return true;
    }

    return false;
}

bool Parser::ParseExEquals(bool expect)
{
    if (ParseExConcat(false))
    {
        if (Accept(TokenType::OP_EQUALS) ||
            Accept(TokenType::OP_NOT_EQUALS))
        {
            ParseExEquals(true);
        }

        return true;
    }

    return false;
}

bool Parser::ParseExConcat(bool expect)
{
    if (ParseExCompare(false))
    {
        if (Accept(TokenType::OP_CONCAT))
        {
            ParseExConcat(true);
        }

        return true;
    }

    return false;
}

bool Parser::ParseExCompare(bool expect)
{
    if (ParseExAdd(false))
    {
        if (Accept(TokenType::OP_LESS_THAN) ||
            Accept(TokenType::OP_GREATER_THAN) ||
            Accept(TokenType::OP_GREATER_THAN_EQUAL) ||
            Accept(TokenType::OP_LESS_THAN_EQUAL))
        {
            ParseExCompare(true);
        }

        return true;
    }

    return false;
}

bool Parser::ParseExAdd(bool expect)
{
    if (ParseExMul(false))
    {
        if (Accept(TokenType::OP_ADD) ||
            Accept(TokenType::OP_SUBTRACT))
        {
            ParseExAdd(true);
        }

        return true;
    }

    return false;
}

bool Parser::ParseExMul(bool expect)
{
    if (ParseExPrefix(false))
    {
        if (Accept(TokenType::OP_MULTIPLY) ||
            Accept(TokenType::OP_DIVIDE) ||
            Accept(TokenType::OP_MODULO))
        {
            ParseExMul(true);
        }

        return true;
    }

    return false;
}

bool Parser::ParseExPrefix(bool expect)
{
    if (Accept(TokenType::OP_NOT) ||
        Accept(TokenType::OP_INCREMENT) ||
        Accept(TokenType::OP_DECREMENT) ||
        Accept(TokenType::OP_SUBTRACT))
    {
        ParseExPrefix(true);

    }
    else if (ParseExPostfix(false))
    {
        return true;
    }

    return false;
}

bool Parser::ParseExPostfix(bool expect)
{
    if (ParseTerm(false))
    {

        return true;
    }

    return false;
}

bool Parser::ParseTerm(bool expect)
{
    auto tokenType = m_currentLexer->Current()->Type;
    if (ParseConstant(false))
    {
        return true;
    }
    else if (ParseParens(false))
    {
        return true;
    }
    else if (tokenType == TokenType::IDENT)
    {

        return true;
    }
    else if (tokenType == TokenType::ATOM)
    {
        return true;
    }

    return false;
}

bool Parser::ParseConstant(bool expect)
{
    auto tokenType = m_currentLexer->Current()->Type;
    if(ParseList(false) ||
       ParseMap(false))
    {
        return true;
    }
    else if (tokenType == TokenType::NUMBER)
    {
        return true;
    }
    else if (tokenType == TokenType::BOOL)
    {

    }
    else if (tokenType == TokenType::TERMINAL)
    {
        
    }

    return false;
}

bool Parser::ParseParens(bool expect)
{
    if(Accept(TokenType::RPAREN))
    {
        if (ParseExpression(true))
        {
            Expect(TokenType::LPAREN);
            return true;
        }
    }
    
    return false;
}

bool Parser::ParseReturn(bool expect)
{
    if(Accept(TokenType::K_RETURN))
    {
        if(ParseExpression(true))
        {
            Expect(TokenType::SEMI);
            return true;
        }
    }
    return false;
}

bool Parser::ParseVarDecl(bool expect)
{
    if(Accept(TokenType::K_VAR))
    {
        if(Accept(TokenType::IDENT))
        {
            Expect(TokenType::OP_ASSIGN);
            if(ParseExpression(true))
            {
                return true;
            }
        }
    }

    return false;
}

bool Parser::ParseBlock(bool expect)
{
    return false;
}

bool Parser::ParseIf(bool expect)
{
    if (Accept(TokenType::K_IF))
    {
        Expect(TokenType::LPAREN);
        if(ParseExpression(true))
        {
            return true;
        }
    }

    return false;
}

bool Parser::ParseWhileLoop(bool expect)
{
    return false;
}

bool Parser::ParseForLoop(bool expect)
{
    return false;
}

bool Parser::ParseList(bool expect)
{
    return false;
}

bool Parser::ParseMap(bool expect)
{
    return false;
}