#include "generation.hpp"
#include "ProgramParseTreeNode.hpp"

#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>

#include <string>
#include <unordered_map>

void generate_file(const ProgramParseTreeNode& program, const std::string& file_path, const std::string& format) {
  auto* gvc = gvContext();
  auto* graph_name = const_cast<char*>("graph");
  auto* graph = agopen(graph_name, Agdirected, NULL);
  agattr(graph, AGNODE, const_cast<char*>("shape"), const_cast<char*>("circle"));
  std::unordered_map<std::string, Agnode_t*> nodes;
  int initial_id = 0;
  for (auto it = program.states_begin(); it != program.states_end(); ++it) {
    auto* node = agnode(graph, const_cast<char*>(it->name().c_str()), TRUE);
    nodes[it->name()] = node;
    if (it->initial()) {
      auto id = "initial" + std::to_string(initial_id);
      auto* dummy_node = agnode(graph, const_cast<char*>(""), TRUE);
      agset(dummy_node, const_cast<char*>("shape"), const_cast<char*>("none"));
      agedge(graph, dummy_node, node, NULL, TRUE);
    }
    if (it->accepting()) {
      agset(node, const_cast<char*>("shape"), const_cast<char*>("doublecircle"));
    }
  }
  int edge_id = 0;
  for (auto it = program.transitions_begin(); it != program.transitions_end(); ++it) {
    auto* from = nodes[it->from()];
    auto* to = nodes[it->to()];
    auto id = "edge" + std::to_string(edge_id++);
    std::string label;
    if (it->symbol()) {
      label = std::string{*it->symbol()};
    } else {
      label = "epsilon";
    }
    auto* edge = agedge(graph, from, to, const_cast<char*>(id.c_str()), TRUE);
    agsafeset(edge, const_cast<char*>("label"), const_cast<char*>(label.c_str()), const_cast<char*>(""));
  }
  gvLayout(gvc, graph, "sfdp");
  gvRenderFilename(gvc, graph, format.c_str(), file_path.c_str());
  gvFreeLayout(gvc, graph);
  agclose(graph);
  gvFreeContext(gvc);
}

void generate_dot(const ProgramParseTreeNode& program, const std::string& file_path) {
  generate_file(program, file_path, "dot");
}

void generate_gif(const ProgramParseTreeNode& program, const std::string& file_path) {
  generate_file(program, file_path, "gif");
}

void generate_png(const ProgramParseTreeNode& program, const std::string& file_path) {
  generate_file(program, file_path, "png");
}

void generate_postscript(const ProgramParseTreeNode& program, const std::string& file_path) {
  generate_file(program, file_path, "ps");
}

void generate_svg(const ProgramParseTreeNode& program, const std::string& file_path) {
  generate_file(program, file_path, "svg");
}
