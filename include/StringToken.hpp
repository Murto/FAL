#pragma once

#include "Token.hpp"

#include <string>


template <typename Kind>
class StringToken final : public Token<Kind> {

public:
  
  StringToken(Kind kind, std::string string)
  : Token<Kind>(kind), m_string{string} {}

  const std::string& string() {
    return m_string;
  }

private:

  const std::string m_string;

};
