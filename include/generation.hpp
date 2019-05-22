#pragma once

#include "ProgramParseTreeNode.hpp"

#include <string>

/*! @file */

/*!
 * @brief Generates a dot file with the given file path from the given FAL program.
 *
 * @param program   - The given FAL program
 * @param file_path - The given file path
 */
void generate_dot(const ProgramParseTreeNode& program, const std::string& file_path);

/*!
 * @brief Generates a gif file with the given file path from the given FAL program.
 *
 * @param program   - The given FAL program
 * @param file_path - The given file path
 */
void generate_gif(const ProgramParseTreeNode& program, const std::string& file_path);

/*!
 * @brief Generates a png file with the given file path from the given FAL program.
 *
 * @param program   - The given FAL program
 * @param file_path - The given file path
 */
void generate_png(const ProgramParseTreeNode& program, const std::string& file_path);

/*!
 * @brief Generates a postscript file with the given file path from the given FAL program.
 *
 * @param program   - The given FAL program
 * @param file_path - The given file path
 */
void generate_postscript(const ProgramParseTreeNode& program, const std::string& file_path);

/*!
 * @brief Generates an svg file with the given file path from the given FAL program.
 *
 * @param program   - The given FAL program
 * @param file_path - The given file path
 */
void generate_svg(const ProgramParseTreeNode& program, const std::string& file_path);
