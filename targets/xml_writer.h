// $Id: xml_writer.h,v 1.3 2016/07/01 00:22:52 ist178596 Exp $ -*- c++ -*-
#ifndef __OOK_SEMANTICS_XMLWRITER_H__
#define __OOK_SEMANTICS_XMLWRITER_H__

#include <string>
#include <iostream>
#include <cdk/ast/basic_node.h>
#include <cdk/symbol_table.h>
#include "targets/basic_ast_visitor.h"
#include "targets/symbol.h"

namespace ook {

  /**
   * Print nodes as XML elements to the output stream.
   */
  class xml_writer: public basic_ast_visitor {
    cdk::symbol_table<ook::symbol> &_symtab;

  public:
    xml_writer(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<ook::symbol> &symtab) :
        basic_ast_visitor(compiler), _symtab(symtab) {
    }

  public:
    ~xml_writer() {
      os().flush();
    }

  private:
    inline void openTag(const std::string &tag, int lvl) {
      os() << std::string(lvl, ' ') + "<" + tag + ">" << std::endl;
    }
    inline void openTag(const cdk::basic_node *node, int lvl) {
      openTag(node->name(), lvl);
    }
    inline void closeTag(const std::string &tag, int lvl) {
      os() << std::string(lvl, ' ') + "</" + tag + ">" << std::endl;
    }
    inline void closeTag(const cdk::basic_node *node, int lvl) {
      closeTag(node->name(), lvl);
    }

  public:
    void do_sequence_node(cdk::sequence_node * const node, int lvl);

  protected:
    template<typename T>
    void processSimple(cdk::simple_value_node<T> * const node, int lvl) {
      os() << std::string(lvl, ' ') << "<" << node->name() << ">" << node->value() << "</" << node->name() << ">" << std::endl;
    }

  public:
    void do_integer_node(cdk::integer_node * const node, int lvl);
    void do_string_node(cdk::string_node * const node, int lvl);

  protected:
    void processUnaryExpression(cdk::unary_expression_node * const node, int lvl);

  public:
    void do_neg_node(cdk::neg_node * const node, int lvl);

  protected:
    void processBinaryExpression(cdk::binary_expression_node * const node, int lvl);

  public:
    void do_add_node(cdk::add_node * const node, int lvl);
    void do_sub_node(cdk::sub_node * const node, int lvl);
    void do_mul_node(cdk::mul_node * const node, int lvl);
    void do_div_node(cdk::div_node * const node, int lvl);
    void do_mod_node(cdk::mod_node * const node, int lvl);
    void do_lt_node(cdk::lt_node * const node, int lvl);
    void do_le_node(cdk::le_node * const node, int lvl);
    void do_ge_node(cdk::ge_node * const node, int lvl);
    void do_gt_node(cdk::gt_node * const node, int lvl);
    void do_ne_node(cdk::ne_node * const node, int lvl);
    void do_eq_node(cdk::eq_node * const node, int lvl);

  public:
    void do_lvalue_node(ook::lvalue_node * const node, int lvl);
    void do_rvalue_node(ook::rvalue_node * const node, int lvl);

  public:
    void do_program_node(ook::program_node * const node, int lvl);
    void do_evaluation_node(ook::evaluation_node * const node, int lvl);
    void do_print_node(ook::print_node * const node, int lvl);
    void do_read_node(ook::read_node * const node, int lvl);
    void do_assignment_node(ook::assignment_node * const node, int lvl);

  public:
    void do_while_node(ook::while_node * const node, int lvl);
    void do_if_node(ook::if_node * const node, int lvl);
    void do_if_else_node(ook::if_else_node * const node, int lvl);

// ------------------ NEW NODES GO BELOW THIS LINE---------------------

  public:
    void do_and_node(ook::and_node * const node, int lvl);
    void do_continue_node(ook::continue_node * const node, int lvl);
    void do_identity_node(ook::identity_node * const node, int lvl);
    void do_not_node(ook::not_node * const node, int lvl);
    void do_or_node(ook::or_node * const node, int lvl);
    void do_return_node(ook::return_node * const node, int lvl);
    void do_simple_lvalue_node(ook::simple_lvalue_node * const node, int lvl);
    void do_index_lvalue_node(ook::index_lvalue_node * const node, int lvl);
    void do_memory_alloc_node(ook::memory_alloc_node * const node, int lvl);
    void do_memory_address_node(ook::memory_address_node * const node, int lvl);
    void do_func_call_node(ook::func_call_node * const node, int lvl);
    void do_func_def_node(ook::func_def_node * const node, int lvl);
    void do_func_decl_node(ook::func_decl_node * const node, int lvl);    
    void do_break_node(ook::break_node * const node, int lvl);    
    void do_block_node(ook::block_node * const node, int lvl);
    void do_variable_decl_node(ook::variable_decl_node * const node, int lvl);
    
  };

} // ook

#endif
