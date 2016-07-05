// $Id: print_node.h,v 1.3 2016/06/29 18:34:36 ist178596 Exp $ -*- c++ -*-
#ifndef __OOK_PRINTNODE_H__
#define __OOK_PRINTNODE_H__

#include <cdk/ast/expression_node.h>

namespace ook {

  /**
   * Class for describing print nodes.
   */
  class print_node: public cdk::basic_node {
    cdk::expression_node *_argument;
    bool _newline;


  public:
    inline print_node(int lineno, cdk::expression_node *argument, bool newline) :
        cdk::basic_node(lineno), _argument(argument), _newline(newline) {
    }

  public:
    inline cdk::expression_node *argument() {
      return _argument;
    }

    const bool& newline() { return _newline; }


    void accept(basic_ast_visitor *sp, int level) {
      sp->do_print_node(this, level);
    }

  };

} // ook

#endif
