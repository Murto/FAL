#pragma once

/*!
 * @brief Represents a lexical token of the given kind.
 * @author Murray Steele
 *
 * @tparam Kind - The given kind
 */
template <typename Kind>
class Token {

public:

  /*!
   * @brief Constructs a token of the given kind.
   *
   * @param kind - The given kind
   */
  Token(Kind kind)
  : m_kind{kind} {}

  
  /*!
   * @brief Default virtual constructor.
   *        Ensures the destructors of derived types are called.
   */
  virtual ~Token() = default;

  /*!
   * @brief Returns the kind of the Token.
   *
   * @return the kind of the Token
   */
  Kind kind() const {
    return m_kind;
  }

private:

  const Kind m_kind; //!< The kind of the token.

};
