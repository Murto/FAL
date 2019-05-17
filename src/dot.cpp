#include "ProgramParseTreeNode.hpp"
#include "semantics.hpp"
#include "StateDeclParseTreeNode.hpp"
#include "TransitionDeclParseTreeNode.hpp"

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

#include <sstream>
#include <string>
#include <unordered_map>


std::string generate_dot(const ProgramParseTreeNode& program) {
  using EdgeWeightProperty = boost::property<boost::edge_weight_t, int>;
  using GraphType = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property, EdgeWeightProperty>;
  assert_semantics(program);
  GraphType graph;
  std::unordered_map<std::string, int> descriptors;
  int i = 0;
  for (auto it = program.states_begin(); it != program.states_end(); ++it) {
    descriptors[it->name()] = i;
    ++i;
  }
  for (auto it = program.transitions_begin(); it != program.transitions_end(); ++it) {
    auto from = descriptors[it->from()];
    auto to = descriptors[it->to()];
    if (it->symbol()) {
      boost::add_edge(from, to, graph);
    } else {
      boost::add_edge(from, to, graph);
    }
  }

  std::ostringstream dot;
  boost::write_graphviz(dot, graph);
  return dot.str();
}
