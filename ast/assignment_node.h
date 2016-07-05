// $Id: assignment_node.h,v 1.2 2016/06/24 12:55:28 ist13500 Exp $ -*- c++ -*-
#ifndef __OOK_ASSIGNMENTNODE_H__
#define __OOK_ASSIGNMENTNODE_H__

#include "ast/lvalue_node.h"

namespace ook {

  /**
   * Class for describing assignment nodes.
   */
  class assignment_node: public cdk::expression_node {
    ook::lvalue_node *_lvalue;
    cdk::expression_node *_rvalue;

  public:
    inline assignment_node(int lineno, ook::lvalue_node *lvalue, cdk::expression_node *rvalue) :
        cdk::expression_node(lineno), _lvalue(lvalue), _rvalue(rvalue) {
    }

  public:
    inline ook::lvalue_node *lvalue() {
      return _lvalue;
    }
    inline cdk::expression_node *rvalue() {
      return _rvalue;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_assignment_node(this, level);
    }

  };

} // ook

#endif
