#ifndef __OOK_SIMPLELVALUENODE_H__
#define __OOK_SIMPLELVALUENODE_H__

#include "lvalue_node.h"
#include <string>

namespace ook {

  /**
   * Class for describing syntactic tree leaves for holding lvalues.
   */
  class simple_lvalue_node: public ook::lvalue_node {
    std::string _identifier;

  public:
    inline simple_lvalue_node(int lineno, const std::string* identifier) :
        ook::lvalue_node(lineno), _identifier(*identifier) {}

    inline const std::string & identifier () {
      return _identifier;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_simple_lvalue_node(this, level);
    }

  };

} // ook

#endif
