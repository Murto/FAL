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

  auto states_begin() const {
    return m_states.cbegin();
  }

  auto states_end() const {
    return m_states.cend();
  }

  auto transitions_begin() const {
    return m_transitions.cbegin();
  }

  auto transitions_end() const {
    return m_transitions.cend();
  }

  auto state_count() const {
    return m_states.size();
  }

  auto transition_count() const {
    return m_states.size();
  }

private:

  StateDeclContainerType m_states;
  TransitionDeclContainerType m_transitions;

};
