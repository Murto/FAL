#pragma once

#include "Token.hpp"
#include "TokenKind.hpp"

/*!
 * @brief Represents a token of a given kind with an associated character value.
 * @author Murray Steele
 *
 * @tparam Kind - The given kind of token
 */
template <typename Kind>
class CharacterToken final : public Token<Kind> {

public:
  
  /*!
   * @brief Constructs a CharacterToken as the given kind of token and character value.
   *
   * @param kind      - The given kind of token
   * @param character - The given character value
   */
  CharacterToken(Kind kind, char character)
  : Token<Kind>(kind), m_character{character} {}

  /*!
   * @brief Returns the character value of the CharacterToken.
   *
   * @return const reference to the character value
   */
  const char& character() {
    return m_character;
  }

private:

  const char m_character; //!< The character value of the CharacterToken.

};
