// $Id: rvalue_node.h,v 1.2 2016/06/24 12:55:28 ist13500 Exp $
#ifndef __OOK_RVALUE_NODE_H__
#define __OOK_RVALUE_NODE_H__

#include <cdk/ast/expression_node.h>
#include "ast/lvalue_node.h"

namespace ook {

  /**
   * Class for describing rvalue nodes.
   */
  class rvalue_node: public cdk::expression_node {
    lvalue_node *_lvalue;

  public:
    inline rvalue_node(int lineno, lvalue_node *lvalue) :
        cdk::expression_node(lineno), _lvalue(lvalue) {
    }

  public:
    inline cdk::expression_node *lvalue() {
      return _lvalue;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_rvalue_node(this, level);
    }

  };

} // ook

#endif
