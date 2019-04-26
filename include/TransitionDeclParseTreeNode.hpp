#pragma once

#include "ParseTreeNode.hpp"

#include <optional>
#include <string>


class TransitionDeclParseTreeNode : public ParseTreeNode {

public:

  TransitionDeclParseTreeNode(std::string from, std::optional<char> symbol, std::string to)
  : m_from{from}, m_symbol{symbol}, m_to{to} {}

  const std::string& from() const {
    return m_from;
  }

  const std::string& to() const {
    return m_to;
  }

  const std::optional<char>& symbol() const {
    return m_symbol;
  }

private:

  std::string m_from;
  std::optional<char> m_symbol;
  std::string m_to;

};
