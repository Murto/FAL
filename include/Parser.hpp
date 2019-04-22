#pragma once

#include "StringToken.hpp"
#include "Token.hpp"
#include "Tokeniser.hpp"
#include "TokenKind.hpp"

#include <memory>


template <typename IteratorType>
class Parser {

public:

  using TokeniserType = Tokeniser<IteratorType>;
  using TokenType = typename TokeniserType::TokenType;

  Parser(IteratorType begin, IteratorType end)
  : m_tokeniser{begin, end} {}

  void parse() {
    parse_state_decl();
    auto lookahead = peek_token()->kind();
    while (lookahead != TokenKind::EOI) {
      switch (lookahead) {
        case TokenKind::STATE: {
          parse_state_decl();
          break;
        }
        case TokenKind::TRANSITION: {
          parse_transition_decl();
          break;
        }
        default: {
          throw std::runtime_error{"Parsing error"};
        }
      }
    }
  }

private:

  TokeniserType m_tokeniser;
  std::shared_ptr<TokenType> m_lookahead{};

  std::shared_ptr<TokenType> read_token() {
    if (m_lookahead) {
      auto lookahead = m_lookahead;
      m_lookahead.reset();
      return lookahead;
    } else {
      return m_tokeniser.read();
    }
  }

  std::shared_ptr<TokenType> peek_token() {
    if (m_lookahead) {
      return m_lookahead;
    } else {
      m_lookahead = m_tokeniser.read();
      return m_lookahead;
    }
  }

  std::shared_ptr<TokenType> expect(TokenKind kind) {
    auto token = read_token();
    if (token->kind() == kind) {
      return token;
    }
    throw std::runtime_error{"Parsing error"};
  }

  template <typename CallbackType>
  void maybe(TokenKind kind, CallbackType callback) {
    if (peek_token()->kind() == kind) {
      callback(read_token());
    }
  }

  void parse_state_decl() {
    expect(TokenKind::STATE);
    expect(TokenKind::STRING);
    maybe(TokenKind::INITIAL, [] (auto token) {});
    maybe(TokenKind::ACCEPTING, [] (auto token) {});
  }

  void parse_transition_decl() {
    expect(TokenKind::TRANSITION);
    expect(TokenKind::STRING);
    expect(TokenKind::RIGHTARROW);
    auto lookahead = peek_token()->kind();
    if (lookahead == TokenKind::CHARACTER || lookahead == TokenKind::EPSILON) {
      read_token();
    } else {
      throw std::runtime_error{"Parsing error"};
    }
    expect(TokenKind::RIGHTARROW);
    expect(TokenKind::STRING);
  }

};

template <typename IteratorType>
Parser<IteratorType> make_parser(IteratorType begin, IteratorType end) {
  return {begin, end};
}
