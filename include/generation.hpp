#pragma once

#include "ProgramParseTreeNode.hpp"

#include <string>


void generate_dot(const ProgramParseTreeNode& program, const std::string& file_path);
void generate_png(const ProgramParseTreeNode& program, const std::string& file_path);
