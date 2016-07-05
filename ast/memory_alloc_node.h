#ifndef __OOK_MEM_ALLOC_NODE_H__
#define __OOK_MEM_ALLOC_NODE_H__

#include <cdk/ast/unary_expression_node.h>

namespace ook {

  /**
   * Class for describing memory allocation nodes.
   */
  class memory_alloc_node: public cdk::unary_expression_node {

    public:
      inline memory_alloc_node(int lineno, cdk::expression_node *argument) :
        cdk::unary_expression_node(lineno, argument) {
        }

      void accept(basic_ast_visitor *sp, int level) {
        sp->do_memory_alloc_node(this, level);
      }
  };
} // ook

#endif
