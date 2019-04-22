#pragma once

#include <stdexcept>


enum class TokenKind {
  STATE,
  INITIAL,
  ACCEPTING,
  TRANSITION,
  RIGHTARROW,
  EPSILON,
  STRING,
  CHARACTER,
  EOI
};

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
