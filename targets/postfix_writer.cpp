// $Id: postfix_writer.cpp,v 1.3 2016/07/01 00:22:52 ist178596 Exp $ -*- c++ -*-
#include <string>
#include <sstream>
#include "targets/type_checker.h"
#include "targets/postfix_writer.h"
#include "ast/all.h"  // all.h is automatically generated

//---------------------------------------------------------------------------
//     THIS IS THE VISITOR'S DEFINITION
//---------------------------------------------------------------------------

void ook::postfix_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }
}

//---------------------------------------------------------------------------

void ook::postfix_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  _pf.INT(node->value()); // push an integer
}

void ook::postfix_writer::do_string_node(cdk::string_node * const node, int lvl) {
  int lbl1;

  /* generate the string */
  _pf.RODATA(); // strings are DATA readonly
  _pf.ALIGN(); // make sure we are aligned
  _pf.LABEL(mklbl(lbl1 = ++_lbl)); // give the string a name
  _pf.STR(node->value()); // output string characters

  /* leave the address on the stack */
  _pf.TEXT(); // return to the TEXT segment
  _pf.ADDR(mklbl(lbl1)); // the string to be printed
}

//---------------------------------------------------------------------------

void ook::postfix_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->argument()->accept(this, lvl); // determine the value
  _pf.NEG(); // 2-complement
}

//---------------------------------------------------------------------------

void ook::postfix_writer::do_add_node(cdk::add_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.ADD();
}
void ook::postfix_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.SUB();
}
void ook::postfix_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MUL();
}
void ook::postfix_writer::do_div_node(cdk::div_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.DIV();
}
void ook::postfix_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MOD();
}
void ook::postfix_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LT();
}
void ook::postfix_writer::do_le_node(cdk::le_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LE();
}
void ook::postfix_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GE();
}
void ook::postfix_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GT();
}
void ook::postfix_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.NE();
}
void ook::postfix_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.EQ();
}

//---------------------------------------------------------------------------

void ook::postfix_writer::do_rvalue_node(ook::rvalue_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->lvalue()->accept(this, lvl);
  _pf.LOAD(); //FIXME: depends on type size
}

//---------------------------------------------------------------------------

void ook::postfix_writer::do_lvalue_node(ook::lvalue_node * const node, int lvl) {
  /*CHECK_TYPES(_compiler, _symtab, node);
  // simplified generation: all variables are global
  _pf.ADDR(node->value());*/
}

//---------------------------------------------------------------------------

void ook::postfix_writer::do_assignment_node(ook::assignment_node * const node, int lvl) {
  /*CHECK_TYPES(_compiler, _symtab, node);

  // DAVID: horrible hack!
  // (this is caused by Ook not having explicit variable declarations)
  const std::string &id = node->lvalue()->value();
  std::shared_ptr<ook::symbol> symbol = _symtab.find(id);
  if (symbol->value() == -1) {
    _pf.DATA(); // variables are all global and live in DATA
    _pf.ALIGN(); // make sure we are aligned
    _pf.LABEL(id); // name variable location
    _pf.CONST(0); // initialize it to 0 (zero)
    _pf.TEXT(); // return to the TEXT segment
    symbol->value(0);
  }

  node->rvalue()->accept(this, lvl); // determine the new value
  _pf.DUP();
  node->lvalue()->accept(this, lvl); // where to store the value
  _pf.STORE(); // store the value at address*/
}

//---------------------------------------------------------------------------

void ook::postfix_writer::do_program_node(ook::program_node * const node, int lvl) {
  // Note that Ook doesn't have functions. Thus, it doesn't need
  // a function node. However, it must start in the main function.
  // The ProgramNode (representing the whole program) doubles as a
  // main function node.

  // generate the main function (RTS mandates that its name be "_main")
  _pf.TEXT();
  _pf.ALIGN();
  _pf.GLOBAL("_main", _pf.FUNC());
  _pf.LABEL("_main");
  _pf.ENTER(0);  // Ook doesn't implement local variables

  node->statements()->accept(this, lvl);

  // end the main function
  _pf.INT(0);
  _pf.POP();
  _pf.LEAVE();
  _pf.RET();

  // these are just a few library function imports
  _pf.EXTERN("readi");
  _pf.EXTERN("printi");
  _pf.EXTERN("prints");
  _pf.EXTERN("println");
}

//---------------------------------------------------------------------------

void ook::postfix_writer::do_evaluation_node(ook::evaluation_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->argument()->accept(this, lvl); // determine the value
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.TRASH(4); // delete the evaluated value
  }
  else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.TRASH(4); // delete the evaluated value's address
  }
  else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
}

void ook::postfix_writer::do_print_node(ook::print_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->argument()->accept(this, lvl); // determine the value to print
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.CALL("printi");
    _pf.TRASH(4); // delete the printed value
  }
  else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.CALL("prints");
    _pf.TRASH(4); // delete the printed value's address
  }
  else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
  _pf.CALL("println"); // print a newline
}

//---------------------------------------------------------------------------

void ook::postfix_writer::do_read_node(ook::read_node * const node, int lvl) {
  /*CHECK_TYPES(_compiler, _symtab, node);
  _pf.CALL("readi");
  _pf.PUSH();
  node->argument()->accept(this, lvl);
  _pf.STORE();*/
}

//---------------------------------------------------------------------------

void ook::postfix_writer::do_while_node(ook::while_node * const node, int lvl) {
  int lbl1, lbl2;
  _pf.LABEL(mklbl(lbl1 = ++_lbl));
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl2 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl1));
  _pf.LABEL(mklbl(lbl2));
}

//---------------------------------------------------------------------------

void ook::postfix_writer::do_if_node(ook::if_node * const node, int lvl) {
  int lbl1;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1));
}

//---------------------------------------------------------------------------

void ook::postfix_writer::do_if_else_node(ook::if_else_node * const node, int lvl) {
  int lbl1, lbl2;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->thenblock()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl2 = ++_lbl));
  _pf.LABEL(mklbl(lbl1));
  node->elseblock()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1 = lbl2));
}

//-----------------------new nodes below this comment------------------------

void ook::postfix_writer::do_and_node(ook::and_node * const node, int lvl){
  //To Do
}

void ook::postfix_writer::do_continue_node(ook::continue_node * const node, int lvl){
  //To Do
}

void ook::postfix_writer::do_identity_node(ook::identity_node * const node, int lvl){
  //To Do
}

void ook::postfix_writer::do_not_node(ook::not_node * const node, int lvl){
  //To Do
}

void ook::postfix_writer::do_or_node(ook::or_node * const node, int lvl){
  //To Do
}

void ook::postfix_writer::do_return_node(ook::return_node * const node, int lvl){
  //To Do
}

void ook::postfix_writer::do_simple_lvalue_node(ook::simple_lvalue_node * const node, int lvl){
  //To Do
}

void ook::postfix_writer::do_index_lvalue_node(ook::index_lvalue_node * const node, int lvl){
  //To Do
}

void ook::postfix_writer::do_memory_address_node(ook::memory_address_node * const node, int lvl){
  //To Do
}

void ook::postfix_writer::do_memory_alloc_node(ook::memory_alloc_node * const node, int lvl){
  //To Do
}

void ook::postfix_writer::do_func_call_node(ook::func_call_node * const node, int lvl){
  //To Do
}
void ook::postfix_writer::do_func_def_node(ook::func_def_node * const node, int lvl){
  //To Do
}
void ook::postfix_writer::do_func_decl_node(ook::func_decl_node * const node, int lvl){
  //To Do
}   

void ook::postfix_writer::do_break_node(ook::break_node * const node, int lvl){
  //To Do
} 

void ook::postfix_writer::do_block_node(ook::block_node * const node, int lvl){
  //To Do
}   

void ook::postfix_writer::do_variable_decl_node(ook::variable_decl_node * const node, int lvl){

}