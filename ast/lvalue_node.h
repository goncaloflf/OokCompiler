#ifndef __OOK_LVALUE_NODE_H__
#define __OOK_LVALUE_NODE_H__

#include <cdk/ast/expression_node.h>

namespace ook {

  /**
   * Abstract Class for describing syntactic tree leaves for holding lvalues.
   */
  class lvalue_node: public cdk::expression_node {
  public:
    inline lvalue_node(int lineno) :
        cdk::expression_node(lineno) {}

    virtual void accept(basic_ast_visitor *sp, int level) = 0;

  };

} // ook

#endif
