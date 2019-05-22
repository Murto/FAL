#pragma once

#include "ParseTreeNode.hpp"

#include <string>

/*!
 * @brief Represents the FAL STATE-DECL production.
 * @author Murray Steele
 */
class StateDeclParseTreeNode final : public ParseTreeNode {

public:

  /*!
   * @brief Constructs a StateDeclParseTreeNode with the given name, inital flag and accepting flag.
   *
   * @param name      - The given name
   * @param initial   - The given initial flag
   * @param accepting - The given accepting flag
   */
  StateDeclParseTreeNode(std::string name, bool initial = false, bool accepting = false)
  : m_name{name}, m_initial{initial}, m_accepting{accepting} {}

  /*!
   * @brief Returns the name of the state associated with the STATE-DECL production.
   *
   * @return the name of the state associated with the STATE-DECL production
   */
  const std::string& name() const {
    return m_name;
  }

  /*!
   * @brief Returns true if the STATE-DECL is for an initial state and false otherwise.
   *
   * @return true if the STATE-DECL is for an initial state and false otherwise.
   */
  const bool& initial() const {
    return m_initial;
  }

  /*!
   * @brief Returns true if the STATE-DECL production is for an accepting state and false otherwise.
   *
   * @return true if the STATE-DECL production is for an accepting state and false otherwise.
   */
  const bool& accepting() const {
    return m_accepting;
  }

private:

  std::string m_name; //!< The name of the state associated with the STATE-DECL production.
  bool m_initial;     //!< A flag indicating if the state associated with the STATE-DECL production is an initial state.
  bool m_accepting;   //!< A flag indicating if the state associated with the STATE-DECL production is an accepting state.

};
