#include "ProgramParseTreeNode.hpp"
#include "semantics.hpp"
#include "StateDeclParseTreeNode.hpp"
#include "TransitionDeclParseTreeNode.hpp"

#include <stdexcept>
#include <string>
#include <unordered_set>

/*!
 * @brief Asserts that all FAL language semantics are adhered to by the given program.
 *
 * @param program - The given program
 *
 * @throw std::runtime_error if any FAL language semantics are not adhered to
 */
void assert_semantics(const ProgramParseTreeNode& program) {
  assert_discrete_state_names(program);
  assert_transition_states_existance(program);
  assert_initial_state_existance(program);
}

/*!
 * @brief Asserts that the given program has discrete states names.
 *
 * @param program - The given program
 *
 * @throw std::runtime_error if any two states have the same name
 */
void assert_discrete_state_names(const ProgramParseTreeNode& program) {
  std::unordered_set<std::string> state_names;
  for (auto it = program.states_begin(); it != program.states_end(); ++it) {
    if (state_names.find(it->name()) == state_names.end()) {
      state_names.insert(it->name());
    } else {
      throw std::runtime_error{"Semantic error"};
    }
  }
}

/*!
 * @brief Asserts that all states referenced by transitions, in the given program, exist.
 *
 * @param program - The given program
 *
 * @throw std::runtime_error if any states referenced by transitions do not exist
 */
void assert_transition_states_existance(const ProgramParseTreeNode& program) {
  std::unordered_set<std::string> state_names;
  for (auto it = program.states_begin(); it != program.states_end(); ++it) {
    state_names.insert(it->name());
  }
  for (auto it = program.transitions_begin(); it != program.transitions_begin(); ++it) {
    if (state_names.find(it->from()) == state_names.end()) {
      throw std::runtime_error{"Semantic error"};
    }
    if (state_names.find(it->to()) == state_names.end()) {
      throw std::runtime_error{"Semantic error"};
    }
  }
}

/*!
 * @brief Asserts that the given program has at least one initial state
 *
 * @param program - The given program
 *
 * @throw std::runtime_error if the program does not contain an initial state
 */
void assert_initial_state_existance(const ProgramParseTreeNode& program) {
  for (auto it = program.states_begin(); it != program.states_end(); ++it) {
    if (it->initial()) {
      return;
    } 
  }
  throw std::runtime_error{"Semantic error"};
}
