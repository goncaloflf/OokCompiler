#ifndef __OOK_FUNCTION_CALL_NODE__H_
#define __OOK_FUNCTION_CALL_NODE__H_

#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include <string>

namespace ook {
  /**
   * Class for describing function call nodes
   */
  class func_call_node : public cdk::expression_node {
    private:
      std::string _identifier;
      cdk::sequence_node * _arguments;
    public:
      inline func_call_node (int lineno,
          const std::string * identifier,
          cdk::sequence_node * arguments):
        cdk::expression_node(lineno), _identifier(*identifier), _arguments(arguments) {}

    public:
      inline const std::string & identifier() {
        return _identifier;
      }

      inline cdk::sequence_node * arguments() {
        return _arguments;
      }

      void accept(basic_ast_visitor *sp, int level) {
        sp->do_func_call_node(this, level);
      }

  };

} // zu

#endif
