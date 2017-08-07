#pragma once

enum TokenType
{
    // Errors
    LEXERR_UNKNOWN_SYMBOL = -1,

    IDENT   = 1,
    BOOL    = 2,
    NUMBER  = 3,
    SEMI    = 4,
    ATOM    = 5,
    COMMA   = 6,
    COLON   = 7,
    COMMENT = 8,

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
    OP_MODULO             = 24,
    OP_GREATER_THAN       = 25,
    OP_GREATER_THAN_EQUAL = 26,
    OP_LESS_THAN          = 27,
    OP_LESS_THAN_EQUAL    = 28,
    OP_EQUALS             = 29,
    OP_NOT_EQUALS         = 30,
    OP_NOT                = 31,
    OP_ASSIGN             = 32,
    OP_CONCAT             = 33,
    OP_MUL_ASSIGN         = 34,
    OP_DIV_ASSIGN         = 35,
    OP_SUB_ASSIGN         = 36,
    OP_ADD_ASSIGN         = 37,
    OP_CONCAT_ASSIGN      = 38,
    OP_INCREMENT          = 39,
    OP_DECREMENT          = 40,
    OP_AND                = 41,
    OP_OR                 = 42,

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
    int Line   = 0;
    int Column = 0;
    union {
        int iValue;
        float fValue;
        const char* sValue;
        bool bValue;
    };
};