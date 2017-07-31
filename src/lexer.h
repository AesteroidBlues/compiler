#pragma once
#include <string>
#include "types.h"

class Lexer
{
    public:
      Lexer(const std::string &sourceStr);
      std::shared_ptr<Token> Current() { return m_current; }
      void Advance();

    private:
      char GetNext();
      std::string m_source;
      std::shared_ptr<Token> m_current;

      char m_currentChar;
      std::string m_currentIdentifier;
      std::string m_currentNumber;
      int m_index;
};