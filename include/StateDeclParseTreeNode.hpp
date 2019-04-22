#pragma once

#include "ParseTreeNode.hpp"

#include <string>


class StateDeclParseTreeNode final : public ParseTreeNode {

public:

  StateDeclParseTreeNode(std::string name, bool initial = false, bool accepting = false)
  : m_name{name}, m_initial{initial}, m_accepting{accepting} {}

  const std::string& name() const {
    return m_name;
  }

  const bool& initial() const {
    return m_initial;
  }

  const bool& accepting() const {
    return m_accepting;
  }

private:

  std::string m_name;
  bool m_initial;
  bool m_accepting;

};
