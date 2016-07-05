#ifndef __OOK_FUNCTION_DECL_H__
#define __OOK_FUNCTION_DECL_H__

#include <cdk/ast/expression_node.h>
#include <cdk/ast/sequence_node.h>

namespace ook {
  /**
   * Class for describing function declaration nodes
   */
  class func_decl_node : public cdk::basic_node {
    basic_type * _type;
    std::string _identifier;
    cdk::sequence_node * _parameters;
    cdk::expression_node * _value;

    bool _is_private;
    bool _is_imported;

    public:
    inline func_decl_node(int lineno,
        basic_type * type,
        const std::string * identifier,
        cdk::sequence_node * parameters,
        cdk::expression_node * value,
        bool is_private,
        bool is_imported):
      cdk::basic_node(lineno), _type(type), _identifier(*identifier),
      _parameters(parameters), _value(value), _is_private(is_private),
      _is_imported(is_imported) {}

    public:

    inline basic_type *type() {
      return _type;
    }

    void type(basic_type * type) {
      type = _type;
    }

    inline const std::string &identifier() {
      return _identifier;
    }

    inline void identifier(const std::string & identifier) {
      _identifier = identifier;
    }

    inline cdk::expression_node *value() {
      return _value;
    }

    inline cdk::sequence_node *parameters() {
      return _parameters;
    }

    inline bool is_private() { return _is_private; }
    inline bool is_imported()  { return _is_imported; }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_func_decl_node(this, level);
    }

  };

} // ook

#endif
