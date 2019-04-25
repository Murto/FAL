#include "ProgramParseTreeNode.hpp"
#include "semantics.hpp"
#include "StateDeclParseTreeNode.hpp"
#include "TransitionDeclParseTreeNode.hpp"

#include <sstream>
#include <string>


std::string generate_dot(const ProgramParseTreeNode& program) {
  analyse_semantics(program);
  std::ostringstream dot_out;
  dot_out << "digraph fal {\n";
  for (auto it = program.states_begin(); it != program.states_end(); ++it) {
    dot_out << "  \"" << it->name() << "\"\n";
  }
  for (auto it = program.transitions_begin(); it != program.transitions_end(); ++it) {
    dot_out << "  \"" << it->from() << "\" -> \"" << it->to() << "\"\n";
  }
  dot_out << '}';
  return dot_out.str();
}
