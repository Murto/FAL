#pragma once

#include <stdexcept>

/*! @file */

/*!
 * @brief FAL lexical token kinds.
 *        See language specification for more information.
 * @author Murray Steele
 */
enum class TokenKind {
  STATE,      //!< String "state".
  INITIAL,    //!< String "initial".
  ACCEPTING,  //!< String "accepting".
  TRANSITION, //!< String "transition".
  RIGHTARROW, //!< String "->".
  EPSILON,    //!< String "epsilon".
  STRING,     //!< String matching regex "[a-zA-Z0-9_-]+"
  CHARACTER,  //!< ? any ascii character excluding whitespace ?.
  EOI         //!< End of input.
};

/*!
 * @brief Returns the string representation of a given TokenKind member.
 *
 * @param kind - The given TokenKind member
 *
 * @throw std::runtime_error if the given TokenKind member is undeclared
 *
 * @return a string representation of the given TokenKind member
 */
std::string to_string(TokenKind kind) {
  switch (kind) {
    case TokenKind::STATE: return "STATE";
    case TokenKind::INITIAL: return "INITIAL";
    case TokenKind::ACCEPTING: return "ACCEPTING";
    case TokenKind::TRANSITION: return "TRANSITION";
    case TokenKind::RIGHTARROW: return "RIGHTARROW";
    case TokenKind::EPSILON: return "EPSILON";
    case TokenKind::STRING: return "STRING";
    case TokenKind::CHARACTER: return "CHARACTER";
    case TokenKind::EOI: return "EOI";
  }
  throw std::runtime_error{"Unknown TokenKind"};
}
