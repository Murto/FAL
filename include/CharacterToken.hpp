#pragma once

#include "Token.hpp"
#include "TokenKind.hpp"


template <typename Kind>
class CharacterToken final : Token<Kind> {

public:
  
  CharacterToken(Kind kind, char character)
  : Token<Kind>(kind), m_character{character} {}

  const char& character() {
    return m_character;
  }

private:

  const char m_character;

};
