#pragma once

#include "ParseTreeNode.hpp"
#include "StateDeclParseTreeNode.hpp"
#include "TransitionDeclParseTreeNode.hpp"

#include <stdexcept>
#include <vector>


/*!
 * @brief Represents the FAL PROGRAM production.
 * @author Murray Steele
 */
class ProgramParseTreeNode : public ParseTreeNode {

public:

  using StateDeclContainerType = std::vector<StateDeclParseTreeNode>;           //!< The container type for STATE-DECL parse tree nodes
  using TransitionDeclContainerType = std::vector<TransitionDeclParseTreeNode>; //!< The container type for TRANSITION-DECL parse tree nodes

  /*!
   * @brief Constructs a ProgramParseTreeNode with the given STATE-DECL and TRANSITION-DECL parse tree nodes.
   *
   * @param states      - The given STATE-DECL parse tree nodes
   * @param transitions - The given TRANSITION-DECL parse tree nodes
   *
   * @throw std::runtime_error if no STATE-DECL parse tree nodes are given
   */
  ProgramParseTreeNode(std::vector<StateDeclParseTreeNode> states, std::vector<TransitionDeclParseTreeNode> transitions)
  : m_states{std::move(states)}, m_transitions{std::move(transitions)} {
    if (states.empty()) {
      throw std::runtime_error{"Must have at least one state"};
    }
  }

  /*!
   * @brief Returns a begin iterator to the program states.
   *
   * @return begin iterator to the program states
   */
  auto states_begin() const {
    return m_states.cbegin();
  }

  /*!
   * @brief Returns a end iterator to the program states
   *
   * @return a end iterator to the program states
   */
  auto states_end() const {
    return m_states.cend();
  }

  /*!
   * @brief Returns a begin iterator to the program transitions.
   *
   * @return a begin iterator to the program states
   */
  auto transitions_begin() const {
    return m_transitions.cbegin();
  }

  /*!
   * @brief Returns an end iterator to the program transitions.
   *
   * @return an end iterator to the program states
   */
  auto transitions_end() const {
    return m_transitions.cend();
  }

  /*!
   * @brief Returns the number of STATE-DECL parse tree nodes in the program.
   *
   * @return the number of STATE-DECL parse tree nodes
   */
  auto state_count() const {
    return m_states.size();
  }

  /*!
   * @brief Returns the number of TRANSITION-DECL parse tree nodes in the program.
   *
   * @return the number of TRANSITION-DECL parse tree nodes
   */
  auto transition_count() const {
    return m_transitions.size();
  }

private:

  StateDeclContainerType m_states;           //!< Container of STATE-DECL parse tree nodes.
  TransitionDeclContainerType m_transitions; //!< Container of TRANSITIONS-DECL parse tree nodes.

};
