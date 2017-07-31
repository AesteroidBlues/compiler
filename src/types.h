#pragma once

enum TokenType
{
    // Errors
    LEXERR_UNKNOWN_SYMBOL = -1,

    IDENT  = 1,
    BOOL   = 2,
    NUMBER = 3,
    SEMI   = 4,
    ATOM   = 5,
    COMMA  = 6,
    COLON  = 7,

    LPAREN = 10,
    RPAREN = 11,
    LBRACE = 12,
    RBRACE = 13,
    LBRACK = 14,
    RBRACK = 15,

    OP_DIVIDE             = 20,
    OP_MULTIPLY           = 21,
    OP_ADD                = 22,
    OP_SUBTRACT           = 23,
    OP_GREATER_THAN       = 24,
    OP_GREATER_THAN_EQUAL = 25,
    OP_LESS_THAN          = 26,
    OP_LESS_THAN_EQUAL    = 27,
    OP_EQUALS             = 28,
    OP_ASSIGN             = 29,

    K_FUNCTION = 30,
    K_VAR      = 31,
    K_IF       = 32,
    K_WHILE    = 33,
    K_FOR      = 35,
    K_IN       = 36,
    K_RETURN   = 37,
    
    END = 999,
};

class Token 
{
public:
    TokenType Type;
    union 
    {
        int iValue;
        float fValue;
        const char* sValue;
        bool bValue;
    };
};