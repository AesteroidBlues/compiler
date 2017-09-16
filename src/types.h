#pragma once
#include <vector>
#include <string>

enum TokenType
{
    // Errors
    LEXERR_UNKNOWN_SYMBOL,

    IDENT,
    BOOL,
    NUMBER,
    TERMINAL,
    SEMI,
    ATOM,
    COMMA,
    COLON,
    COMMENT,

    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    LBRACK,
    RBRACK,

    OP_DIVIDE,
    OP_MULTIPLY,
    OP_ADD,
    OP_SUBTRACT,
    OP_MODULO,
    OP_GREATER_THAN,
    OP_GREATER_THAN_EQUAL,
    OP_LESS_THAN,
    OP_LESS_THAN_EQUAL,
    OP_EQUALS,
    OP_NOT_EQUALS,
    OP_NOT,
    OP_ASSIGN,
    OP_CONCAT,
    OP_MUL_ASSIGN,
    OP_DIV_ASSIGN,
    OP_SUB_ASSIGN,
    OP_ADD_ASSIGN,
    OP_CONCAT_ASSIGN,
    OP_INCREMENT,
    OP_DECREMENT,
    OP_AND,
    OP_OR,

    K_FUNCTION,
    K_VAR,
    K_IF,
    K_WHILE,
    K_FOR,
    K_IN,
    K_RETURN,

    PROGRAM_START,
    END,
};

class Token 
{
public:
    TokenType Type;
    int Line;
    int Column;

    std::string Identifier;
    union {
        int iValue;
        float fValue;
        const char* sValue;
        bool bValue;
    };
};