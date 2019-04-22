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

  auto begin_states() {
    return m_states.begin();
  }

  auto begin_states() const {
    return m_states.cbegin();
  }

  auto end_states() {
    return m_states.end();
  }

  auto end_states() const {
    return m_states.cend();
  }

  auto begin_transitions() {
    return m_transitions.begin();
  }

  auto begin_transitions() const {
    return m_transitions.cbegin();
  }

  auto end_transitions() {
    return m_transitions.end();
  }

  auto end_transitions() const {
    return m_transitions.cend();
  }

private:

  StateDeclContainerType m_states;
  TransitionDeclContainerType m_transitions;

};
