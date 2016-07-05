#ifndef __OOK_FUNCTION_DEF_H__
#define __OOK_FUNCTION_DEF_H__

#include <cdk/ast/expression_node.h>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/identifier_node.h>
#include "func_decl_node.h"

namespace ook {
  /**
   * Class for describing function definition nodes
   */
  class func_def_node : public cdk::basic_node {
    basic_type * _type;
    std::string _identifier;
    cdk::sequence_node * _parameters;
    cdk::expression_node * _value;

    bool _is_private;

    cdk::basic_node * _block;

    public:
    inline func_def_node(int lineno,
        basic_type * type,
        const std::string * identifier,
        cdk::sequence_node * parameters,
        cdk::expression_node * value,
        bool is_private,
        cdk::basic_node * block):
      cdk::basic_node(lineno), _type(type), _identifier(*identifier),
      _parameters(parameters), _value(value), _is_private(is_private),
      _block(block) {}

    inline func_def_node(int lineno,
        ook::func_decl_node * fdecl,
        cdk::basic_node * block):
      cdk::basic_node(lineno), _type(fdecl->type()), _identifier(fdecl->identifier()),
      _parameters(fdecl->parameters()), _value(fdecl->value()),
      _is_private(fdecl->is_private()), _block(block) {}

    public:
    inline basic_type *type() {
      return _type;
    }

    void type(basic_type *type) {
      _type = type;
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

    inline cdk::basic_node *block()  { return _block; }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_func_def_node(this, level);
    }

  };

} // ook

#endif

