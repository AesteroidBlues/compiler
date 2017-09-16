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
    { "for", TokenType::K_FOR },
    { "if", TokenType::K_IF },
    { "while", TokenType::K_WHILE },
    { "return", TokenType::K_RETURN },
};

std::unordered_map<std::string, TokenType> operatorMap =
{
    { "/", TokenType::OP_DIVIDE },
    { "*", TokenType::OP_MULTIPLY },
    { "+", TokenType::OP_ADD },
    { "-", TokenType::OP_SUBTRACT },
    { "%%", TokenType::OP_MODULO },
    { ">", TokenType::OP_GREATER_THAN },
    { ">=", TokenType::OP_GREATER_THAN_EQUAL },
    { "<", TokenType::OP_LESS_THAN },
    { "<=", TokenType::OP_LESS_THAN_EQUAL },
    { "==", TokenType::OP_EQUALS },
    { "!=", TokenType::OP_NOT_EQUALS },
    { "!", TokenType::OP_NOT },
    { "=", TokenType::OP_ASSIGN },
    { "#", TokenType::OP_CONCAT },
    { "*=", TokenType::OP_MUL_ASSIGN },
    { "/=", TokenType::OP_DIV_ASSIGN },
    { "-=", TokenType::OP_SUB_ASSIGN },
    { "+=", TokenType::OP_ADD_ASSIGN },
    { "#=", TokenType::OP_CONCAT_ASSIGN },
    { "++", TokenType::OP_INCREMENT },
    { "--", TokenType::OP_DECREMENT },
    { "&&", TokenType::OP_AND },
    { "||", TokenType::OP_OR },
    // Makes parsing logic simpler
    { "|", TokenType::LEXERR_UNKNOWN_SYMBOL },
    { "&", TokenType::LEXERR_UNKNOWN_SYMBOL },
};

Lexer::Lexer(const std::string &sourceStr) :
    m_source(sourceStr),
    m_index(0),
    m_lineColumn(0),
    m_lineNumber(0)
{
    m_currentChar = sourceStr[0];
    Advance(); // Get the first token ready to go
}

void Lexer::Advance() 
{
    // Make a new token
    m_current = std::make_shared<Token>();

    SkipWhitespace();

    // COMMENTS
    if (m_currentChar == '/')
    {
        m_currentChar = GetNext();
        if (m_currentChar == '/')
        {
            do
            {
                m_currentChar = GetNext();
                // Might run off the end of the file while parsing comments
                if (m_currentChar == '\0')
                {
                    m_current->Type = TokenType::END;
                    return;
                }
            } while (m_currentChar != '\n');
        }
    }

    SkipWhitespace();

    // PARENS
    auto paren = parenMap.find(m_currentChar);
    if (paren != parenMap.end())
    {
        m_current->Type = paren->second;
        m_currentChar = GetNext();
        return;
    }

    // SEMICOLONS
    if (m_currentChar == ';')
    {
        m_current->Type = TokenType::SEMI;
        m_currentChar = GetNext();
        return;
    }

    // NUMBERS
    if (std::isdigit(m_currentChar))
    {
        // Parse ints for now
        do
        {
            m_currentNumber += m_currentChar;
            m_currentChar = GetNext();
        } while (std::isdigit(m_currentChar));

        int number = std::stoi(m_currentNumber);
        m_current->Type = TokenType::NUMBER;
        m_current->iValue = number;
        return;
    }

    std::string op(1, m_currentChar);
    auto opIter = operatorMap.find(op);
    if (opIter != operatorMap.end())
    {
        m_current->Type = opIter->second;

        // it's possible our op is part of a 2-char op (like GTE)
        m_currentChar = GetNext();
        op += m_currentChar;
        opIter = operatorMap.find(op);
        if (opIter != operatorMap.end())
        {
            m_current->Type = opIter->second;
            m_currentChar = GetNext();
        }

        m_current->Line = m_lineNumber;
        m_current->Column = m_lineColumn;

        return;
    }

    if (m_currentChar == '@')
    {
        m_currentChar = GetNext();
        if (std::isalpha(m_currentChar) || m_currentChar == '_')
        {
            m_currentIdentifier = GetIdentifier();
            m_current->Type = TokenType::ATOM;
            m_current->Identifier = m_currentIdentifier;
        }

        m_currentIdentifier.clear();
        return;
    }

    if (std::isalpha(m_currentChar) || m_currentChar == '_')
    {
        m_currentIdentifier = GetIdentifier();

        auto keyword = keywordMap.find(m_currentIdentifier);
        if (keyword != keywordMap.end())
        {
            m_current->Type = keyword->second;
        } 
        else 
        {
            m_current->Type = TokenType::IDENT;
            m_current->Identifier = m_currentIdentifier;
        }

        m_currentIdentifier.clear();
        return;
    }

    if (m_currentChar == '\0')
    {
        m_current->Type = TokenType::END;
        return;
    }
}

std::string Lexer::GetIdentifier()
{
    std::string s;
    do
    {
        s += m_currentChar;
        m_currentChar = GetNext();
    } while (std::isalnum(m_currentChar) || m_currentChar == '_');

    return s;
}

char Lexer::GetNext()
{
    m_lineColumn++;
    return m_source[++m_index];
}

char Lexer::PeekNext()
{
    return m_source[m_index + 1];
}

void Lexer::SkipWhitespace()
{
    // Advance past white space
    while(std::isspace(m_currentChar))
    {
        if (m_currentChar == '\n')
        {
            m_lineNumber++;
            m_lineColumn = 0;
        }
        
        m_currentChar = GetNext();
    }
}