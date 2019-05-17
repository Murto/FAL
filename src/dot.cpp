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
  struct VertexProperties { std::string name; };
  struct EdgeProperties { std::string name; };
  using GraphType = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexProperties, EdgeProperties>;
  assert_semantics(program);
  GraphType graph{program.state_count()};
  std::unordered_map<std::string, int> descriptors;
  int i = 0;
  for (auto it = program.states_begin(); it != program.states_end(); ++it) {
    descriptors[it->name()] = i;
    graph[i].name = it->name();
    ++i;
  }
  for (auto it = program.transitions_begin(); it != program.transitions_end(); ++it) {
    auto from = descriptors[it->from()];
    auto to = descriptors[it->to()];
    if (it->symbol()) {
      boost::add_edge(from, to, {std::string{1, *it->symbol()}}, graph);
    } else {
      boost::add_edge(from, to, {std::string{"epsilon"}}, graph);
    }
  }
  
  std::ostringstream dot;
  boost::write_graphviz(dot, graph, boost::make_label_writer(get(&VertexProperties::name, graph)), boost::make_label_writer(get(&EdgeProperties::name, graph)));
  return dot.str();
}
