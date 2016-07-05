#ifndef __OOK_NOTNODE_H__
#define __OOK_NOTNODE_H__

#include <cdk/ast/unary_expression_node.h>

namespace ook {

  /**
   * Class for describing the not ('~') operator
   */
  class not_node: public cdk::unary_expression_node {
  public:
    /**
     * @param lineno source code line number for this node
     * @param expr operand
     */
    inline not_node(int lineno, cdk::expression_node *expr) :
        unary_expression_node(lineno, expr) {
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_not_node(this, level);
    }

  };

} // ook

#endif
