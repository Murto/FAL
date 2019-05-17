#pragma once

#include "ProgramParseTreeNode.hpp"

#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>

#include <string>
#include <unordered_map>


void generate_png(const ProgramParseTreeNode& program, const std::string& file_path);
