// compiler.cpp : Defines the entry point for the console application.
//

#include "lexer.h"
#include <iostream>

std::string test =
"                   \n\
// Comment          \n\
function foo(bar) { \n\
    return 2 >= 4;  \n\
}                   \n\
";

TokenType testArr[] =
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

int main()
{
    std::cout << "Starting" << std::endl;

    auto lexer = Lexer(test);
    auto current = lexer.Current();
    
    int i = 0;
    while (current->Type != TokenType::END)
    {
        if(current->Type != testArr[i])
        {
            std::cout << "FAIL: " << current->Type << " != " << testArr[i] << std::endl;
            return -1;
        }
        lexer.Advance();
        i++;
    }

    std::cout << "SUCCESS!" << std::endl;
    return 0;
}

