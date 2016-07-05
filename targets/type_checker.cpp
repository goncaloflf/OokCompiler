// $Id: type_checker.cpp,v 1.3 2016/07/01 00:22:52 ist178596 Exp $ -*- c++ -*-
#include <string>
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

#define ASSERT_UNSPEC \
    { if (node->type() != nullptr && \
          node->type()->name() != basic_type::TYPE_UNSPEC) return; }

//---------------------------------------------------------------------------

void ook::type_checker::do_integer_node(cdk::integer_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void ook::type_checker::do_string_node(cdk::string_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_STRING));
}

//---------------------------------------------------------------------------

inline void ook::type_checker::processUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in argument of unary expression");

  // in Ook, expressions are always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void ook::type_checker::do_neg_node(cdk::neg_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

inline void ook::type_checker::processBinaryExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in right argument of binary expression");

  // in Ook, expressions are always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void ook::type_checker::do_add_node(cdk::add_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_sub_node(cdk::sub_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_mul_node(cdk::mul_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_div_node(cdk::div_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_mod_node(cdk::mod_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_lt_node(cdk::lt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_le_node(cdk::le_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_ge_node(cdk::ge_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_gt_node(cdk::gt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_ne_node(cdk::ne_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::type_checker::do_eq_node(cdk::eq_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void ook::type_checker::do_rvalue_node(ook::rvalue_node * const node, int lvl) {
  node->lvalue()->accept(this, lvl);
  node->type(node->lvalue()->type());
}

//---------------------------------------------------------------------------

void ook::type_checker::do_lvalue_node(ook::lvalue_node * const node, int lvl) {
  /*const std::string &id = node->value();
  std::shared_ptr<ook::symbol> symbol = _symtab.find(id);
  if (symbol == nullptr) throw id + " undeclared";
  // hackish stuff...
  node->type(new basic_type(4, basic_type::TYPE_INT));*/
}

//---------------------------------------------------------------------------

void ook::type_checker::do_assignment_node(ook::assignment_node * const node, int lvl) {
  /*ASSERT_UNSPEC;

  // DAVID: horrible hack!
  // (this is caused by Ook not having explicit variable declarations)
  const std::string &id = node->lvalue()->value();
  if (!_symtab.find(id)) {
    _symtab.insert(id, std::make_shared<ook::symbol>(new basic_type(4, basic_type::TYPE_INT), id, -1)); // put in the symbol table
  }

  node->lvalue()->accept(this, lvl + 2);
  if (node->lvalue()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in left argument of assignment expression");

  node->rvalue()->accept(this, lvl + 2);
  if (node->rvalue()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in right argument of assignment expression");

  // in Ook, expressions are always int
  node->type(new basic_type(4, basic_type::TYPE_INT));*/
}

//---------------------------------------------------------------------------

void ook::type_checker::do_evaluation_node(ook::evaluation_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

void ook::type_checker::do_print_node(ook::print_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

//---------------------------------------------------------------------------

void ook::type_checker::do_read_node(ook::read_node * const node, int lvl) {
  //node->argument()->accept(this, lvl + 2);
}

//---------------------------------------------------------------------------

void ook::type_checker::do_while_node(ook::while_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

//---------------------------------------------------------------------------

void ook::type_checker::do_if_node(ook::if_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

void ook::type_checker::do_if_else_node(ook::if_else_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

//----------------NEW NODES BELOW THIS LINE--------------------------

void ook::type_checker::do_and_node(ook::and_node * const node, int lvl){
  //To Do
}

void ook::type_checker::do_continue_node(ook::continue_node * const node, int lvl){
  //To Do
}

void ook::type_checker::do_identity_node(ook::identity_node * const node, int lvl){
  //To Do
}

void ook::type_checker::do_not_node(ook::not_node * const node, int lvl){
  //To Do
}

void ook::type_checker::do_or_node(ook::or_node * const node, int lvl){
  //To Do
}

void ook::type_checker::do_return_node(ook::return_node * const node, int lvl){
  //To Do
}

void ook::type_checker::do_simple_lvalue_node(ook::simple_lvalue_node * const node, int lvl){
  //To Do
}

void ook::type_checker::do_index_lvalue_node(ook::index_lvalue_node * const node, int lvl){
  //To Do
}

void ook::type_checker::do_memory_address_node(ook::memory_address_node * const node, int lvl){
  //To Do
}

void ook::type_checker::do_memory_alloc_node(ook::memory_alloc_node * const node, int lvl){
  //To Do
}

void ook::type_checker::do_func_call_node(ook::func_call_node * const node, int lvl){
  //To Do
}
void ook::type_checker::do_func_def_node(ook::func_def_node * const node, int lvl){
  //To Do
}
void ook::type_checker::do_func_decl_node(ook::func_decl_node * const node, int lvl){
  //To Do
}   

void ook::type_checker::do_break_node(ook::break_node * const node, int lvl){
  //To Do
}   

void ook::type_checker::do_block_node(ook::block_node * const node, int lvl){
  //To Do
}   

void ook::type_checker::do_variable_decl_node(ook::variable_decl_node * const node, int lvl){

}