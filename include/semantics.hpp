#pragma once

#include "ProgramParseTreeNode.hpp"

/*! @file */

/*!
 * @brief Asserts that all FAL language semantics are adhered to by the given program.
 *
 * @param program - The given program
 *
 * @throw std::runtime_error if any FAL language semantics are not adhered to
 */
void assert_semantics(const ProgramParseTreeNode& program);

/*!
 * @brief Asserts that the given program has discrete states names.
 *
 * @param program - The given program
 *
 * @throw std::runtime_error if any two states have the same name
 */
void assert_discrete_state_names(const ProgramParseTreeNode& program);

/*!
 * @brief Asserts that all states referenced by transitions, in the given program, exist.
 *
 * @param program - The given program
 *
 * @throw std::runtime_error if any states referenced by transitions do not exist
 */
void assert_transition_states_existance(const ProgramParseTreeNode& program);

/*!
 * @brief Asserts that the given program has at least one initial state
 *
 * @param program - The given program
 *
 * @throw std::runtime_error if the program does not contain an initial state
 */
void assert_initial_state_existance(const ProgramParseTreeNode& program);
