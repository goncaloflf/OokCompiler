#ifndef __OOK_RETURNNODE_H__
#define __OOK_RETURNNODE_H__

#include <cdk/ast/expression_node.h>

namespace ook {

  /**
   * Class for describing return nodes.
   */
  class return_node: public cdk::basic_node {
    public:
    inline return_node(int lineno) :
      cdk::basic_node(lineno) {}

    public:

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_return_node(this, level);
    }

  };

} // ook

#endif
