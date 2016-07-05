#ifndef __OOK_CONTINUENODE_H__
#define __OOK_CONTINUENODE_H__

#include <cdk/ast/expression_node.h>

namespace ook {

  /**
   * Class for describing continue nodes.
   */
  class continue_node: public cdk::basic_node {
    public:
    inline continue_node(int lineno) :
      cdk::basic_node(lineno) {}

    public:

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_continue_node(this, level);
    }

  };

} // ook

#endif
