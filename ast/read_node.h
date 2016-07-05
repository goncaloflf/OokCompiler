// $Id: read_node.h,v 1.3 2016/07/01 00:22:52 ist178596 Exp $ -*- c++ -*-
#ifndef __OOK_READNODE_H__
#define __OOK_READNODE_H__

#include "ast/lvalue_node.h"

namespace ook {

  /**
   * Class for describing read nodes.
   */
  class read_node: public cdk::expression_node {

  public:
    inline read_node(int lineno) :
        cdk::expression_node(lineno) {}

  public:

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_read_node(this, level);
    }

  };

} // ook

#endif
