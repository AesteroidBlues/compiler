// compiler.cpp : Defines the entry point for the console application.
//

#include "lexer.h"
#include <iostream>

std::string test = 
"                       \
    function foo(bar) { \
                        \
    }                   \
";

TokenType testArr[] =
{
    TokenType::K_FUNCTION,
    TokenType::IDENT,
    TokenType::LPAREN,
    TokenType::IDENT,
    TokenType::RPAREN,
    TokenType::LBRACE,
    TokenType::RBRACE
};

int main()
{
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

