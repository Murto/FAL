#pragma once

#include "ProgramParseTreeNode.hpp"
#include "StateDeclParseTreeNode.hpp"
#include "TransitionDeclParseTreeNode.hpp"
#include "TokenKind.hpp"

#include <boost/optional.hpp>

#include <memory>

/*! @file */

/*!
 * @brief Used for transforming input from a tokeniser into a parse tree.
 * @author Murray Steele
 *
 * @tparam TokeniserType - The tokeniser type
 */
template <typename TokeniserType>
class Parser {

public:

  using TokenType = typename TokeniserType::TokenType;                   //!< The token type.
  using CharacterTokenType = typename TokeniserType::CharacterTokenType; //!< The tokens-with-associated-character-values type.
  using StringTokenType = typename TokeniserType::StringTokenType;       //!< The tokens-with-associated-string-values type.

  /*!
   * @brief Constructs a Parser with the given tokeniser.
   *
   * @param tokeniser - The given tokeniser
   */
  Parser(TokeniserType tokeniser)
  : m_tokeniser{tokeniser} {}

  /*!
   * @brief Transforms input from the underlying tokeniser into a parse tree.
   *
   * @throw std::runtime_error if input from the tokeniser does not fit the FAL grammer specification
   *
   * @return a parse tree
   */
  ProgramParseTreeNode parse() {
    std::vector<StateDeclParseTreeNode> states;
    std::vector<TransitionDeclParseTreeNode> transitions;
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

  TokeniserType m_tokeniser;                //!< The underlying tokeniser.
  std::shared_ptr<TokenType> m_lookahead{}; //!< A lookahead for the next token to be parsed.

  /*!
   * @brief Reads the next token from the underlying tokeniser.
   *
   * @return a shared pointer to the next token
   */
  std::shared_ptr<TokenType> read_token() {
    if (m_lookahead) {
      auto lookahead = m_lookahead;
      m_lookahead.reset();
      return lookahead;
    } else {
      return m_tokeniser.read();
    }
  }

  /*!
   * @brief Peeks at the next token from the underlying tokeniser.
   *
   * @return a shared pointer to the next token
   */
  std::shared_ptr<TokenType> peek_token() {
    if (m_lookahead) {
      return m_lookahead;
    } else {
      m_lookahead = m_tokeniser.read();
      return m_lookahead;
    }
  }

  /*!
   * @brief Asserts that the next token from the underlying tokeniser is of the given kind.
   *
   * @param kind - The given kind
   *
   * @throw std::runtime_error if the next token is not of the given kind
   *
   * @return a shared pointer to the next token
   */
  std::shared_ptr<TokenType> expect(TokenKind kind) {
    auto token = read_token();
    if (token->kind() == kind) {
      return token;
    }
    throw std::runtime_error{"Parsing error: Expected " + to_string(kind) + ", got " + to_string(token->kind())};
  }

  /*!
   * @brief Reads the next token and passes it into the given callback function, if and only if it is of the given kind.
   *
   * @tparam CallbackType - The given callback function type
   * @param kind          - The given kind
   * @param callback      - The given callback function
   */
  template <typename CallbackType>
  void maybe(TokenKind kind, CallbackType callback) {
    if (peek_token()->kind() == kind) {
      callback(read_token());
    }
  }

  /*!
   * @brief Parses a STATE-DECL as per the FAL language specification.
   *
   * @throw std::runtime_error if input from the underlying tokeniser does not fit the specification for a STATE-DECL
   *
   * @return a STATE-DECL parse tree node
   */
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

  /*!
   * @brief Parses a TRANSITION-DECL as per the FAL language specification.
   *
   * @throw std::runtime_error if input from the underlying tokeniser does not fit the specification for a TRANSITION-DECL
   *
   * @return a TRANSITION-DECL parse tree node
   */
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

/*!
 * @brief Constructs and returns a Parser with the given tokeniser.
 *        Does not require specifying template parameters unlike calling the Parser constructor directly.
 *
 * @return a Parser with the given underlying tokeniser
 */
template <typename TokeniserType>
Parser<TokeniserType> make_parser(TokeniserType tokeniser) {
  return {tokeniser};
}
