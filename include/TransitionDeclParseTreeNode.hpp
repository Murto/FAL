#pragma once

#include "ParseTreeNode.hpp"

#include <boost/optional.hpp>

#include <string>

/*!
 * @brief Represents the FAL TRANSITION-DECL production.
 * @author Murray Steele
 */
class TransitionDeclParseTreeNode : public ParseTreeNode {

public:

  /*!
   * @brief Constructs a TransitionDeclParseTreeNode with the given from-state name, to-state name and optional transition symbol.
   *
   * @param from   - The given from-state name
   * @param symbol - The optional transition symbol
   * @param to     - The given to-state name
   */
  TransitionDeclParseTreeNode(std::string from, boost::optional<char> symbol, std::string to)
  : m_from{std::move(from)}, m_symbol{std::move(symbol)}, m_to{std::move(to)} {}

  /*!
   * @brief Returns the from-state name of the associated TRANSITION-DECL production.
   *
   * @return the from-state name of the associated TRANSITION-DECL production
   */
  const std::string& from() const {
    return m_from;
  }

  /*!
   * @brief Returns the to-state name of the associated TRANSITION-DECL production.
   *
   * @return the to-state name of the associated TRANSITION-DECL production
   */
  const std::string& to() const {
    return m_to;
  }

  /*!
   * @brief Returns the optional transition symbol of the associated TRANSITION-DECL production.
   *
   * @return the optional transition symbol of the associated TRANSITION-DECL production.
   */
  const boost::optional<char>& symbol() const {
    return m_symbol;
  }

private:

  std::string m_from;             //!< The from-state name of the associated TRANSITION-DECL production.
  boost::optional<char> m_symbol; //!< The optional transition symbol of the associated TRANSITION-DECL production.
  std::string m_to;               //!< The to-state name of the associated TRANSITION-DECL production.

};
