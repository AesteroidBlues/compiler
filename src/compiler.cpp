// compiler.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include "lexer.h"
#include "parser.h"

std::string test =
"                   \n\
// Comment          \n\
function foo(bar) { \n\
    return 2 >= 4;  \n\
}                   \n\
";

TokenType testArr[] =
{
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

int main()
{
    std::cout << "Starting" << std::endl;

    auto lexer = std::make_shared<Lexer>(test);
    auto parser = Parser();
    parser.Consume(lexer);
    parser.Finalize();
    std::cout << "Parsing" << std::endl;

    auto ast = parser.GetAST();
    ASTNode::PrintAST(ast);

    std::cout << "Done" << std::endl;
    return 0;
}

