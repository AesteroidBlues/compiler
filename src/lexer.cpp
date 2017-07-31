#include "lexer.h"
#include <cctype>
#include <iostream>
#include <unordered_map>

std::unordered_map<char, TokenType> parenMap =
{
    { '{', TokenType::LBRACE },
    { '}', TokenType::RBRACE },
    { '[', TokenType::LBRACK },
    { ']', TokenType::RBRACK },
    { '(', TokenType::LPAREN },
    { ')', TokenType::RPAREN },
};

std::unordered_map<std::string, TokenType> keywordMap =
{
    { "function", TokenType::K_FUNCTION },
    { "var", TokenType::K_VAR },
};

Lexer::Lexer(const std::string &sourceStr) :
    m_source(sourceStr),
    m_index(0)
{
    m_current = std::make_shared<Token>();
    m_currentChar = sourceStr[0];
    Advance(); // Get the first token ready to go
}

void Lexer::Advance() 
{
    // Advance past white space
    while(std::isspace(m_currentChar))
    {
        m_currentChar = GetNext();
    }

    auto paren = parenMap.find(m_currentChar);
    if(paren != parenMap.end())
    {
        m_current->Type = paren->second;
        m_currentChar = GetNext();
        return;
    }

    if(std::isalnum(m_currentChar))
    {
        do
        {
            m_currentIdentifier += m_currentChar;
            m_currentChar = GetNext();
        } while (std::isalnum(m_currentChar));

        auto keyword = keywordMap.find(m_currentIdentifier);
        if(keyword != keywordMap.end())
        {
            m_current->Type = keyword->second;
        } 
        else 
        {
            m_current->Type = TokenType::IDENT;
        }

        return;
    }

    if(m_currentChar == '\0')
    {
        m_current->Type = TokenType::END;
    }
}

char Lexer::GetNext()
{
    return m_source[++m_index];
}