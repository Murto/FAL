#pragma once

#include "ProgramParseTreeNode.hpp"


void assert_semantics(const ProgramParseTreeNode& program);
void assert_discrete_state_names(const ProgramParseTreeNode& program);
void assert_transition_states_existance(const ProgramParseTreeNode& program);
