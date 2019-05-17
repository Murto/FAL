#pragma once

#include "ParseTreeNode.hpp"

#include <boost/optional.hpp>

#include <string>


class TransitionDeclParseTreeNode : public ParseTreeNode {

public:

  TransitionDeclParseTreeNode(std::string from, boost::optional<char> symbol, std::string to)
  : m_from{from}, m_symbol{symbol}, m_to{to} {}

  const std::string& from() const {
    return m_from;
  }

  const std::string& to() const {
    return m_to;
  }

  const boost::optional<char>& symbol() const {
    return m_symbol;
  }

private:

  std::string m_from;
  boost::optional<char> m_symbol;
  std::string m_to;

};
