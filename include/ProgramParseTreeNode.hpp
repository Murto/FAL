#pragma once

#include "ParseTreeNode.hpp"
#include "StateDeclParseTreeNode.hpp"
#include "TransitionDeclParseTreeNode.hpp"

#include <stdexcept>
#include <vector>


class ProgramParseTreeNode : public ParseTreeNode {

public:

  using StateDeclContainerType = std::vector<StateDeclParseTreeNode>;
  using TransitionDeclContainerType = std::vector<TransitionDeclParseTreeNode>;

  ProgramParseTreeNode(std::vector<StateDeclParseTreeNode> states, std::vector<TransitionDeclParseTreeNode> transitions)
  : m_states{states}, m_transitions{transitions} {
    if (states.empty()) {
      throw std::runtime_error{"Must have at least one state"};
    }
  }

  auto states_begin() {
    return m_states.begin();
  }

  auto states_begin() const {
    return m_states.cbegin();
  }

  auto states_end() {
    return m_states.end();
  }

  auto states_end() const {
    return m_states.cend();
  }

  auto transitions_begin() {
    return m_transitions.begin();
  }

  auto transitions_begin() const {
    return m_transitions.cbegin();
  }

  auto transitions_end() {
    return m_transitions.end();
  }

  auto transitions_end() const {
    return m_transitions.cend();
  }

private:

  StateDeclContainerType m_states;
  TransitionDeclContainerType m_transitions;

};
