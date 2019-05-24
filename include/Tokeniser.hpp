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

/*! @file */

/*!
 * @brief Transforms a sequence of ascii characters defined by an iterator range into a sequence of FAL tokens.
 * @author Murray Steele
 *
 * @tparam IteratorType - The iterator type used to define the ascii character range
 */
template <typename IteratorType>
class Tokeniser {

public:

  using TokenType = Token<TokenKind>;                   //!< The token type.
  using CharacterTokenType = CharacterToken<TokenKind>; //!< The tokens-with-associated-character-values type.
  using StringTokenType = StringToken<TokenKind>;       //!< The tokens-with-associated-string-values type.

  /*!
   * @brief Constructs a Tokeniser with the given iterators describing a character range.
   *
   * @param begin - The beginning of the character range.
   * @param end   - The end of the character range.
   */
  Tokeniser(IteratorType begin, IteratorType end)
  : m_it{begin}, m_end{end} {}

  /*!
   * @brief Reads the next FAL token from the underlying character range.
   *
   * @throw std::runtime_error if no valid token can be read
   *
   * @return a shared pointer to the next FAL token if the remaining range is not empty and a shared pointer to a token of kind TokenKind::EOI otherwise
   */
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
      return std::shared_ptr<TokenType>(new StringTokenType{TokenKind::STRING, unquoted});
    } else if (std::regex_match(buffer, CHARACTER)) {
      return std::shared_ptr<TokenType>(new CharacterTokenType{TokenKind::CHARACTER, buffer[0]});
    }
    throw std::runtime_error{"Tokenisation error: Unknown token \'" + buffer + "\'"};
  }

private:

  static const std::regex STATE;      //!< The regex pattern for a FAL STATE token.
  static const std::regex INITIAL;    //!< The regex pattern for a FAL INITIAL token.
  static const std::regex ACCEPTING;  //!< The regex pattern for a FAL ACCEPTING token.
  static const std::regex TRANSITION; //!< The regex pattern for a FAL TRANSITION token.
  static const std::regex RIGHTARROW; //!< The regex pattern for a FAL RIGHTARROW token.
  static const std::regex EPSILON;    //!< The regex pattern for a FAL EPSILON token.
  static const std::regex STRING;     //!< The regex pattern for a FAL STRING token.
  static const std::regex CHARACTER;  //!< The regex pattern for a FAL CHARACTER token.

  IteratorType m_it;        //!< The begin iterator for the underlying character range.
  const IteratorType m_end; //!< The end iterator for the underlying character range.

  /*!
   * @brief Removes preceding whitespace from the underlying character range.
   */
  void munch_whitespace() {
    while (m_it != m_end && std::isspace(*m_it)) {
      ++m_it;
    }
  }

  /*!
   * @brief Returns the next whitespace-delimited string from the underlying character range.
   *
   * @return the next whitespace-delimited string from the underlying character range
   */
  std::string next_word() {
    std::string buffer;
    while (m_it != m_end && !isspace(*m_it)) {
      buffer += *m_it;
      ++m_it;
    }
    return buffer;
  }

};

/*!
 * @brief The regex pattern for a FAL STATE token.
 */
template <typename IteratorType>
const std::regex Tokeniser<IteratorType>::STATE{"state"};

/*!
 * @brief The regex pattern for a FAL INITIAL token.
 */
template <typename IteratorType>
const std::regex Tokeniser<IteratorType>::INITIAL{"initial"};

/*!
 * @brief The regex pattern for a FAL ACCEPTING token.
 */
template <typename IteratorType>
const std::regex Tokeniser<IteratorType>::ACCEPTING{"accepting"};

/*!
 * @brief The regex pattern for a FAL TRANSITION token.
 */
template <typename IteratorType>
const std::regex Tokeniser<IteratorType>::TRANSITION{"transition"};

/*!
 * @brief The regex pattern for a FAL RIGHTARROW token.
 */
template <typename IteratorType>
const std::regex Tokeniser<IteratorType>::RIGHTARROW{"->"};

/*!
 * @brief The regex pattern for a FAL EPSILON token.
 */
template <typename IteratorType>
const std::regex Tokeniser<IteratorType>::EPSILON{"epsilon"};

/*!
 * @brief The regex pattern for a FAL STRING token.
 */
template <typename IteratorType>
const std::regex Tokeniser<IteratorType>::STRING{"\"[a-zA-Z0-9_-]+\""};

/*!
 * @brief The regex pattern for a FAL CHARACTER token.
 */
template <typename IteratorType>
const std::regex Tokeniser<IteratorType>::CHARACTER{"[^ \t\r\n]"};

/*!
 * @brief Constructs and returns a Tokeniser with the given iterators describing a character range.
 *        Does not require specifying template parameters unlike calling the Tokeniser constructor directly.
 *
 * @param begin - The beginning of the character range
 * @param end   - The end of the character range
 */
template <typename IteratorType>
Tokeniser<IteratorType> make_tokeniser(IteratorType begin, IteratorType end) {
  return {begin, end};
}
