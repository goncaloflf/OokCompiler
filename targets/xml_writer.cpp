// $Id: xml_writer.cpp,v 1.3 2016/07/01 00:22:52 ist178596 Exp $ -*- c++ -*-
#include <string>
#include "targets/xml_writer.h"
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

//---------------------------------------------------------------------------

void ook::xml_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  os() << std::string(lvl, ' ') << "<sequence_node size='" << node->size() << "'>" << std::endl;
  for (size_t i = 0; i < node->size(); i++)
    node->node(i)->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void ook::xml_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  processSimple(node, lvl);
}

void ook::xml_writer::do_string_node(cdk::string_node * const node, int lvl) {
  processSimple(node, lvl);
}

//---------------------------------------------------------------------------

inline void ook::xml_writer::processUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void ook::xml_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

inline void ook::xml_writer::processBinaryExpression(cdk::binary_expression_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void ook::xml_writer::do_add_node(cdk::add_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::xml_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::xml_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::xml_writer::do_div_node(cdk::div_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::xml_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::xml_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::xml_writer::do_le_node(cdk::le_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::xml_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::xml_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::xml_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void ook::xml_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void ook::xml_writer::do_rvalue_node(ook::rvalue_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void ook::xml_writer::do_lvalue_node(ook::lvalue_node * const node, int lvl) {
 /* CHECK_TYPES(_compiler, _symtab, node);
  processSimple(node, lvl);*/
}

//---------------------------------------------------------------------------

void ook::xml_writer::do_assignment_node(ook::assignment_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 2);
  openTag("rvalue", lvl + 2);
  node->rvalue()->accept(this, lvl + 4);
  closeTag("rvalue", lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void ook::xml_writer::do_program_node(ook::program_node * const node, int lvl) {
  openTag(node, lvl);
  node->statements()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void ook::xml_writer::do_evaluation_node(ook::evaluation_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void ook::xml_writer::do_print_node(ook::print_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void ook::xml_writer::do_read_node(ook::read_node * const node, int lvl) {
  /*openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);*/
}

//---------------------------------------------------------------------------

void ook::xml_writer::do_while_node(ook::while_node * const node, int lvl) {
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("block", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("block", lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void ook::xml_writer::do_if_node(ook::if_node * const node, int lvl) {
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  closeTag(node, lvl);
}

void ook::xml_writer::do_if_else_node(ook::if_else_node * const node, int lvl) {
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->thenblock()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  openTag("else", lvl + 2);
  node->elseblock()->accept(this, lvl + 4);
  closeTag("else", lvl + 2);
  closeTag(node, lvl);
}

//----------------NEW NODES BELOW THIS LINE--------------------------

void ook::xml_writer::do_and_node(ook::and_node * const node, int lvl){
  //To Do
}

void ook::xml_writer::do_continue_node(ook::continue_node * const node, int lvl){
  //To Do
}

void ook::xml_writer::do_identity_node(ook::identity_node * const node, int lvl){
  //To Do
}

void ook::xml_writer::do_not_node(ook::not_node * const node, int lvl){
  //To Do
}

void ook::xml_writer::do_or_node(ook::or_node * const node, int lvl){
  //To Do
}

void ook::xml_writer::do_return_node(ook::return_node * const node, int lvl){
  //To Do
}

void ook::xml_writer::do_simple_lvalue_node(ook::simple_lvalue_node * const node, int lvl){
  //To Do
}

void ook::xml_writer::do_index_lvalue_node(ook::index_lvalue_node * const node, int lvl){
  //To Do
}

void ook::xml_writer::do_memory_address_node(ook::memory_address_node * const node, int lvl){
  //To Do
}

void ook::xml_writer::do_memory_alloc_node(ook::memory_alloc_node * const node, int lvl){
  //To Do
}

void ook::xml_writer::do_func_call_node(ook::func_call_node * const node, int lvl){
  //To Do
}

void ook::xml_writer::do_func_def_node(ook::func_def_node * const node, int lvl){
  //To Do
}

void ook::xml_writer::do_func_decl_node(ook::func_decl_node * const node, int lvl){
  //To Do
}   

void ook::xml_writer::do_break_node(ook::break_node * const node, int lvl){
  //To Do
}   

void ook::xml_writer::do_block_node(ook::block_node * const node, int lvl){
  //To Do
}   

void ook::xml_writer::do_variable_decl_node(ook::variable_decl_node * const node, int lvl){

}