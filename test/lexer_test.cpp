#include <iostream>
#include <array>
#include "src/lexer.h"

std::string smokeTest =
"                   \n\
// Comment          \n\
function foo(bar) { \n\
    return 2 >= 4;  \n\
}                   \n\
";

TokenType smokeTestTokens[] =
{
    TokenType::COMMENT,
    TokenType::K_FUNCTION,
    TokenType::IDENT,
    TokenType::LPAREN,
    TokenType::IDENT,
    TokenType::RPAREN,
    TokenType::LBRACE,
    TokenType::K_RETURN,
    TokenType::NUMBER,
    TokenType::OP_GREATER_THAN_EQUAL,
    TokenType::NUMBER,
    TokenType::SEMI,
    TokenType::RBRACE
};

void HandleError(std::shared_ptr<Token> token)
{
    std::cout << "ERROR: ";
    if ( token->Type == TokenType::LEXERR_UNKNOWN_SYMBOL )
    {
        std::cout << "Unknown Symbol on line " << token->Line << " column " << token->Column;
    }

    std::cout << std::endl;
}

bool TestLexer(std::string name, std::string code, TokenType tokens[], int size)
{
    std::cout << name << " - ";

    auto lexer = Lexer(code);
    auto current = lexer.Current();
    
    int i = 0;
    while (i < size)
    {
        if (((int)current->Type) < 0)
        {
            HandleError(current);
            return ;
        }

        if (current->Type != tokens[i])
        {
            std::cout << "FAIL: " << current->Type << " != " << tokens[i] << std::endl;
            return -1;
        }
        lexer.Advance();
        i++;
    }

    std::cout << "PASS" << std::endl;
    return 0;
}

int main()
{
    
}