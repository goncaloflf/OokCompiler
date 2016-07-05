#ifndef __OOK_INDEXLVALUENODE_H__
#define __OOK_INDEXLVALUENODE_H__

#include <cdk/ast/expression_node.h>
#include "lvalue_node.h"

namespace ook {

  /**
   * Class for describing the indexing node
   */
  class index_lvalue_node: public ook::lvalue_node {
    cdk::expression_node *_left;
    cdk::expression_node *_right;
    public:
      inline index_lvalue_node(int lineno, cdk::expression_node *left, cdk::expression_node *right) :
        ook::lvalue_node (lineno),  _left(left), _right(right) {}

      inline cdk::expression_node * left()  { return _left; }
      inline cdk::expression_node * right() { return _right; }

      void accept(basic_ast_visitor *sp, int level) {
        sp->do_index_lvalue_node(this, level);
      }

  };

} // ook

#endif
