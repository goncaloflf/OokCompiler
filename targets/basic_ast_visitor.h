// $Id: basic_ast_visitor.h,v 1.3 2016/07/01 00:22:52 ist178596 Exp $ -*- c++ -*-
#ifndef __OOK_BASIC_AST_VISITOR_H__
#define __OOK_BASIC_AST_VISITOR_H__

#include <string>
#include <memory>
#include <iostream>
#include <cdk/compiler.h>

/* include node forward declarations */
#define __NODE_DECLARATIONS_ONLY__
#include "ast/all.h"  // automatically generated
#undef __NODE_DECLARATIONS_ONLY__

//!
//! Print nodes as XML elements to the output stream.
//!
class basic_ast_visitor {
protected:
  //! The owner compiler
  std::shared_ptr<cdk::compiler> _compiler;

protected:
  basic_ast_visitor(std::shared_ptr<cdk::compiler> compiler) :
      _compiler(compiler) {
  }

  inline bool debug() {
    return _compiler->debug();
  }

  inline std::ostream &os() {
    return *_compiler->ostream();
  }

public:
  virtual ~basic_ast_visitor() {
  }

public:
  // CDK nodes (general)
  virtual void do_nil_node(cdk::nil_node * const node, int lvl) {
    // Ook does not use this node
  }
  virtual void do_data_node(cdk::data_node * const node, int lvl) {
    // Ook does not use this node
  }
  virtual void do_composite_node(cdk::composite_node * const node, int lvl) {
    // Ook does not use this node
  }
  virtual void do_sequence_node(cdk::sequence_node * const node, int lvl) = 0;

public:
  virtual void do_integer_node(cdk::integer_node * const node, int lvl) = 0;
  virtual void do_double_node(cdk::double_node * const node, int lvl) {
    // Ook does not use this node
  }
  virtual void do_string_node(cdk::string_node * const node, int lvl) = 0;
  virtual void do_identifier_node(cdk::identifier_node * const node, int lvl) {
    // Ook does not use this node
  }

public:
  virtual void do_neg_node(cdk::neg_node * const node, int lvl) = 0;

public:
  virtual void do_add_node(cdk::add_node * const node, int lvl) = 0;
  virtual void do_sub_node(cdk::sub_node * const node, int lvl) = 0;
  virtual void do_mul_node(cdk::mul_node * const node, int lvl) = 0;
  virtual void do_div_node(cdk::div_node * const node, int lvl) = 0;
  virtual void do_mod_node(cdk::mod_node * const node, int lvl) = 0;
  virtual void do_lt_node(cdk::lt_node * const node, int lvl) = 0;
  virtual void do_le_node(cdk::le_node * const node, int lvl) = 0;
  virtual void do_ge_node(cdk::ge_node * const node, int lvl) = 0;
  virtual void do_gt_node(cdk::gt_node * const node, int lvl) = 0;
  virtual void do_ne_node(cdk::ne_node * const node, int lvl) = 0;
  virtual void do_eq_node(cdk::eq_node * const node, int lvl) = 0;

public:
  virtual void do_lvalue_node(ook::lvalue_node * const node, int lvl) = 0;
  virtual void do_rvalue_node(ook::rvalue_node * const node, int lvl) = 0;

public:
  virtual void do_program_node(ook::program_node * const node, int lvl) = 0;
  virtual void do_evaluation_node(ook::evaluation_node * const node, int lvl) = 0;
  virtual void do_print_node(ook::print_node * const node, int lvl) = 0;
  virtual void do_read_node(ook::read_node * const node, int lvl) = 0;
  virtual void do_assignment_node(ook::assignment_node * const node, int lvl) = 0;

public:
  virtual void do_while_node(ook::while_node * const node, int lvl) = 0;
  virtual void do_if_node(ook::if_node * const node, int lvl) = 0;
  virtual void do_if_else_node(ook::if_else_node * const node, int lvl) = 0;

//new nodes added below this comment
public:
  virtual void do_and_node(ook::and_node * const node, int lvl) = 0;
  virtual void do_continue_node(ook::continue_node * const node, int lvl) = 0;
  virtual void do_identity_node(ook::identity_node * const node, int lvl) = 0;
  virtual void do_not_node(ook::not_node * const node, int lvl) = 0;
  virtual void do_or_node(ook::or_node * const node, int lvl) = 0;
  virtual void do_return_node(ook::return_node * const node, int lvl) = 0;
  virtual void do_simple_lvalue_node(ook::simple_lvalue_node * const node, int lvl) = 0;
  virtual void do_index_lvalue_node(ook::index_lvalue_node * const node, int lvl) = 0;
  virtual void do_memory_alloc_node(ook::memory_alloc_node * const node, int lvl) = 0;
  virtual void do_memory_address_node(ook::memory_address_node * const node, int lvl) = 0;
  virtual void do_func_call_node(ook::func_call_node * const node, int lvl) = 0;
  virtual void do_func_def_node(ook::func_def_node * const node, int lvl) = 0;
  virtual void do_func_decl_node(ook::func_decl_node * const node, int lvl) = 0;
  virtual void do_break_node(ook::break_node * const node, int lvl) = 0;
  virtual void do_block_node(ook::block_node * const node, int lvl) = 0;
  virtual void do_variable_decl_node(ook::variable_decl_node * const node, int lvl) = 0;


};

#endif
