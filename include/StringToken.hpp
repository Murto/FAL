#pragma once

#include "Token.hpp"

#include <string>

/*!
 * @brief Represents a token of a given kind with an associated string value.
 * @author Murray Steele
 *
 * @tparam Kind - The given kind of token
 */
template <typename Kind>
class StringToken final : public Token<Kind> {

public:
  
  /*!
   * @brief Constructs a StringToken as the given kind of token and string value.
   *
   * @param kind   - The given kind of token
   * @param string - The given string value
   */
  StringToken(Kind kind, std::string string)
  : Token<Kind>(kind), m_string{std::move(string)} {}

  /*!
   * @brief Returns the string value of the StringToken.
   *
   * @return const reference to the string value
   */
  const std::string& string() const {
    return m_string;
  }

private:

  const std::string m_string; //!< The string value of the StringToken.

};
