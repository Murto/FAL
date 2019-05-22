#pragma once

/*!
 * @brief Base class for parse tree nodes.
 * @author Murray Steele
 */
class ParseTreeNode {

public:

  /*!
   * @brief Default virtual constructor.
   *        Ensures the destructors of derived types are called.
   */
  virtual ~ParseTreeNode() = default;

};
