#ifndef __OOK_IDENDITYNODE_H__
#define __OOK_IDENDITYNODE_H__

#include <cdk/ast/unary_expression_node.h>

namespace ook {
  /**
   * Class for describing the identity ('+') operator;
   * not to be confused with the add operator ('+').
   */
  class identity_node: public cdk::unary_expression_node {
  public:
    /**
     * @param lineno source code line number for this node
     * @param expr operand
     */
    inline identity_node(int lineno, cdk::expression_node *expr) :
        unary_expression_node(lineno, expr) {
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_identity_node(this, level);
    }

  };

} // ook

#endif

