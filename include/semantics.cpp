#include "StateDeclTreeNode.hpp"
#include "TransitionDeclTreeNode.hpp"

#include <stdexcept>
#include <string>
#include <unordered_map>


void analyse_semantics(const ProgramParseTreeNode& program) {
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
    if (state_names.find(it->from) == state_names.end()) {
      throw std::runtime_error{"Semantic error"};
    }
    if (state_names.find(it->to) == state_names.end()) {
      throw std::runtime_error{"Semantic error"};
    }
  }
}
