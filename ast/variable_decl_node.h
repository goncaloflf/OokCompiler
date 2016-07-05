#ifndef __OOK_VARIABLE_DECL_H__
#define __OOK_VARIABLE_DECL_H__

#include <cdk/ast/expression_node.h>
#include <cdk/ast/sequence_node.h>

namespace ook {
  /**
   * Class for describing variable declaration nodes
   */
  class variable_decl_node : public cdk::basic_node {
    basic_type * _type;
    std::string _identifier;
    cdk::expression_node *_value;

    bool _is_private;
    bool _is_imported;
    bool _is_argument;

    public:
    inline variable_decl_node(int lineno,
        basic_type * type,
        const std::string * identifier,
        cdk::expression_node * value,
        bool is_private,
        bool is_imported,
        bool is_argument):
      cdk::basic_node(lineno), _type(type), _identifier(*identifier),
      _value(value), _is_private(is_private),
      _is_imported(is_imported), _is_argument(is_argument) {}

    public:
    inline basic_type *type() const {
      return _type;
    }

    inline void type(basic_type * type ) {
      _type = type;
    }

    inline const std::string &identifier() const {
      return _identifier;
    }

    inline cdk::expression_node *value() const {
      return _value;
    }

    inline bool is_private()   const { return _is_private; }
    inline bool is_imported()  const { return _is_imported; }
    inline bool is_argument()  const { return _is_argument; }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_variable_decl_node(this, level);
    }

  };

} // ook

#endif

