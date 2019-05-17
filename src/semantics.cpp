#include "ProgramParseTreeNode.hpp"
#include "StateDeclParseTreeNode.hpp"
#include "TransitionDeclParseTreeNode.hpp"

#include <stdexcept>
#include <string>
#include <unordered_set>


void assert_semantics(const ProgramParseTreeNode& program) {
  std::unordered_set<std::string> state_names;
  bool initial = false;
  for (auto it = program.states_begin(); it != program.states_end(); ++it) {
    state_names.insert(it->name());
    if (it->initial()) {
      initial = true;
    }
  }
  if (!initial) {
    throw std::runtime_error{"Semantic error"};
  }
  for (auto it = program.transitions_begin(); it != program.transitions_end(); ++it) {
    if (state_names.find(it->from()) == state_names.end()) {
      throw std::runtime_error{"Semantic error"};
    }
    if (state_names.find(it->to()) == state_names.end()) {
      throw std::runtime_error{"Semantic error"};
    }
  }
}

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

void assert_initial_state_existance(const ProgramParseTreeNode& program) {
  for (auto it = program.states_begin(); it != program.states_end(); ++it) {
    if (it->initial()) {
      return
    } else {
      throw std::runtime_error{"Semantic error"};
    }
}

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
