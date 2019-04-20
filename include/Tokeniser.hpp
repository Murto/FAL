#pragma once

#include "CharacterToken.hpp"
#include "StringToken.hpp"
#include "Token.hpp"
#include "TokenKind.hpp"

#include <cctype>
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>


template <typename IteratorType>
class Tokeniser {

public:

  using TokenType = Token<TokenKind>;

  Tokeniser(IteratorType begin, IteratorType end)
  : m_it{begin}, m_end{end} {}

  std::shared_ptr<TokenType> read() {
    
    munch_whitespace();

    std::string buffer = next_word();

    if (buffer.empty()) {
      return std::make_shared<TokenType>(TokenKind::EOI);
    }

    if (std::regex_match(buffer, STATE)) {
      return std::make_shared<TokenType>(TokenKind::STATE);
    } else if (std::regex_match(buffer, INITIAL)) {
      return std::make_shared<TokenType>(TokenKind::INITIAL);
    } else if (std::regex_match(buffer, ACCEPTING)) {
      return std::make_shared<TokenType>(TokenKind::ACCEPTING);
    } else if (std::regex_match(buffer, TRANSITION)) {
      return std::make_shared<TokenType>(TokenKind::TRANSITION);
    } else if (std::regex_match(buffer, RIGHTARROW)) {
      return std::make_shared<TokenType>(TokenKind::RIGHTARROW);
    } else if (std::regex_match(buffer, EPSILON)) {
      return std::make_shared<TokenType>(TokenKind::EPSILON);
    } else if (std::regex_match(buffer, STRING)) {
      std::string unquoted = buffer.substr(1, buffer.size() - 2);
      return std::shared_ptr<TokenType>(new StringToken{TokenKind::STRING, unquoted});
    } else if (std::regex_match(buffer, CHARACTER)) {
      return std::shared_ptr<TokenType>(new CharacterToken{TokenKind::CHARACTER, buffer[0]});
    }

    throw std::runtime_error{"Tokenisation error"};
  }

private:

  static const std::regex STATE;
  static const std::regex INITIAL;
  static const std::regex ACCEPTING;
  static const std::regex TRANSITION;
  static const std::regex RIGHTARROW;
  static const std::regex EPSILON;
  static const std::regex STRING;
  static const std::regex CHARACTER;

  IteratorType m_it;
  const IteratorType m_end;

  void munch_whitespace() {
    while (m_it != m_end && std::isspace(*m_it)) {
      ++m_it;
    }
  }

  std::string next_word() {
    std::string buffer;
    while (m_it != m_end && !isspace(*m_it)) {
      buffer += *m_it;
      ++m_it;
    }
    return buffer;
  }

};


template <typename IteratorType>
const std::regex Tokeniser<IteratorType>::STATE{"state"};

template <typename IteratorType>
const std::regex Tokeniser<IteratorType>::INITIAL{"initial"};

template <typename IteratorType>
const std::regex Tokeniser<IteratorType>::ACCEPTING{"accepting"};

template <typename IteratorType>
const std::regex Tokeniser<IteratorType>::TRANSITION{"transition"};

template <typename IteratorType>
const std::regex Tokeniser<IteratorType>::RIGHTARROW{"->"};

template <typename IteratorType>
const std::regex Tokeniser<IteratorType>::EPSILON{"epsilon"};

template <typename IteratorType>
const std::regex Tokeniser<IteratorType>::STRING{"\"[a-zA-Z0-9_-]+\""};

template <typename IteratorType>
const std::regex Tokeniser<IteratorType>::CHARACTER{"[^ \t\r\n]"};

template <typename IteratorType>
Tokeniser<IteratorType> make_tokeniser(IteratorType begin, IteratorType end) {
  return {begin, end};
}
