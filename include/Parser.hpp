#pragma once

#include "ProgramParseTreeNode.hpp"
#include "StateDeclParseTreeNode.hpp"
#include "TransitionDeclParseTreeNode.hpp"
#include "StringToken.hpp"
#include "Token.hpp"
#include "Tokeniser.hpp"
#include "TokenKind.hpp"

#include <boost/optional.hpp>

#include <memory>


template <typename TokeniserType>
class Parser {

public:

  using TokenType = typename TokeniserType::TokenType;
  using CharacterTokenType = typename TokeniserType::CharacterTokenType;
  using StringTokenType = typename TokeniserType::StringTokenType;

  Parser(TokeniserType tokeniser)
  : m_tokeniser{tokeniser} {}

  ProgramParseTreeNode parse() {
    std::vector<StateDeclParseTreeNode> states;
    std::vector<TransitionDeclParseTreeNode> transitions;
    states.push_back(parse_state_decl());
    auto lookahead = peek_token()->kind();
    while (lookahead != TokenKind::EOI) {
      switch (lookahead) {
        case TokenKind::STATE: {
          states.push_back(parse_state_decl());
          break;
        }
        case TokenKind::TRANSITION: {
          transitions.push_back(parse_transition_decl());
          break;
        }
        default: {
          throw std::runtime_error{"Parsing error: Expected STATE or TRANSITION, got " + to_string(lookahead)};
        }
      }
      lookahead = peek_token()->kind();
    }
    return {states, transitions};
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
    throw std::runtime_error{"Parsing error: Expected " + to_string(kind) + ", got " + to_string(token->kind())};
  }

  template <typename CallbackType>
  void maybe(TokenKind kind, CallbackType callback) {
    if (peek_token()->kind() == kind) {
      callback(read_token());
    }
  }

  StateDeclParseTreeNode parse_state_decl() {
    expect(TokenKind::STATE);
    auto token = expect(TokenKind::STRING);
    std::string name;
    if (auto name_token = std::dynamic_pointer_cast<StringTokenType>(token)) {
        name = name_token->string();
    }
    bool initial = false;
    maybe(TokenKind::INITIAL, [&initial] (auto token) { initial = true; });
    bool accepting = false;
    maybe(TokenKind::ACCEPTING, [&accepting] (auto token) { accepting = true; });
    return {name, initial, accepting};
  }

  TransitionDeclParseTreeNode parse_transition_decl() {
    expect(TokenKind::TRANSITION);
    auto from_token = expect(TokenKind::STRING);
    std::string from;
    if (auto string_token = std::dynamic_pointer_cast<StringTokenType>(from_token)) {
        from = string_token->string();
    }
    expect(TokenKind::RIGHTARROW);
    boost::optional<char> symbol;
    auto lookahead = peek_token()->kind();
    if (lookahead == TokenKind::CHARACTER) {
      auto symbol_token = read_token();
      if (auto character_token = std::dynamic_pointer_cast<CharacterTokenType>(symbol_token)) {
          symbol = character_token->character();
      }
    } else {
      expect(TokenKind::EPSILON);
    }
    expect(TokenKind::RIGHTARROW);
    auto to_token = expect(TokenKind::STRING);
    std::string to;
    if (auto string_token = std::dynamic_pointer_cast<StringTokenType>(to_token)) {
        to = string_token->string();
    }
    return {from, symbol, to};
  }

};

template <typename TokeniserType>
Parser<TokeniserType> make_parser(TokeniserType tokeniser) {
  return {tokeniser};
}
