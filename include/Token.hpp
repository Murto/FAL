#pragma once


template <typename Kind>
class Token {

public:

  Token(Kind kind)
  : m_kind{kind} {}

  virtual ~Token() = default;

  Kind kind() {
    return m_kind;
  }

private:

  const Kind m_kind;

};
