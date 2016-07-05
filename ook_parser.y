%{
// $Id: ook_parser.y,v 1.3 2016/07/01 00:31:15 ist178596 Exp $
//-- don't change *any* of these: if you do, you'll break the compiler.
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE       compiler->scanner()->lineno()
#define yylex()    compiler->scanner()->scan()
#define yyerror(s) compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
//-- don't change *any* of these --- END!
%}

%union {
  int                   i;	/* integer value */
  double                d;
  std::string          *s;	/* symbol name or string literal */
  cdk::basic_node      *node;	/* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  ook::lvalue_node  *lvalue;
  basic_type            *type;
  ook::func_decl_node   *fdecl;
};

%token <i> tINTEGER
%token <d> tDOUBLE
%token <s> tIDENTIFIER tSTRING
%token tWHILE tIF tPRINT tREAD tBEGIN tEND tPUBLIC tIMPORT tNEXT tSTOP tRETURN tNULL tINTDECL tDOUBLEDECL tPOINTERDECL tSTRINGDECL tVOID tPRINTLN

%nonassoc pIF
%nonassoc tELSE

%right '='
%left '|'
%left '&'
%nonassoc '~'

%left tEQ tNE
%left tGE tLE '>' '<'
%left '+' '-'
%left '*' '/' '%'

//%nonassoc '?'

%nonassoc pUNARY

%type <s>          litString
%type <type>       type
%type <fdecl>      fdecl
%type <lvalue>     lval
%type <sequence>   fparams args

%type <expression> literal funcall expr arg

%type <sequence>   decls  instrs vardecls params
%type <node>       decl  var  instr  vardecl  param

%type <node>       file
%type <node>       block cond iter

%{
//-- The rules below will be included in yyparse, the main parsing function.
%}
%%

file : decls                    {YYPARSE_PARAM->ast($1); }
     |                          {YYPARSE_PARAM->ast(new cdk::nil_node(LINE));}
     ;

decls : decl	                { $$ = new cdk::sequence_node(LINE, $1); }
     | decls decl               { $$ = new cdk::sequence_node(LINE, $2, $1); }
     ;
     
decl : vardecl                  { $$ = $1; }
     | fdecl                    { $$ = $1; }
     | fdecl block              { $$ = new ook::func_def_node(LINE, $1, $2); }
     ;

vardecls    : vardecl                          { $$ = new cdk::sequence_node(LINE, $1); }
            | vardecls vardecl                 { $$ = new cdk::sequence_node(LINE, $2, $1); }
            ;

vardecl     : var ';'                          { $$ = $1; };


var         : tIMPORT type tIDENTIFIER              { $$ = new ook::variable_decl_node(LINE, $2, $3, NULL,  true,  true, false); }
            | tPUBLIC type tIDENTIFIER              { $$ = new ook::variable_decl_node(LINE, $2, $3, NULL, false, false, false); }
            | type tIDENTIFIER                      { $$ = new ook::variable_decl_node(LINE, $1, $2, NULL,  true, false, false); }
            | tPUBLIC type tIDENTIFIER '=' expr     { $$ = new ook::variable_decl_node(LINE, $2, $3,   $5, false, false, false); }
            | type tIDENTIFIER     '=' expr         { $$ = new ook::variable_decl_node(LINE, $1, $2,   $4,  true, false, false); }
            ;

type        : tINTDECL                              { $$ = new basic_type(4, basic_type::TYPE_INT);    }
            | tDOUBLEDECL                           { $$ = new basic_type(8, basic_type::TYPE_DOUBLE); }
            | tSTRINGDECL                           { $$ = new basic_type(4, basic_type::TYPE_STRING); }
            | tPOINTERDECL                          { $$ = new basic_type(4, basic_type::TYPE_POINTER); }
            ;
     
fdecl       : tPUBLIC tVOID tIDENTIFIER '(' fparams ')'                {$$ = new ook::func_decl_node(LINE, new basic_type(0, basic_type::TYPE_VOID), $3, $5, NULL, false, false); }
            | tIMPORT tVOID tIDENTIFIER '(' fparams ')'                {$$ = new ook::func_decl_node(LINE, new basic_type(0, basic_type::TYPE_VOID), $3, $5, NULL, true, true); }
            | tPUBLIC type tIDENTIFIER '(' fparams ')'                 {$$ = new ook::func_decl_node(LINE, $2, $3, $5, NULL, false, false); }
            | tIMPORT type tIDENTIFIER '(' fparams ')'                 {$$ = new ook::func_decl_node(LINE, $2, $3, $5, NULL, true, true); }
            | tPUBLIC type tIDENTIFIER '(' fparams ')' '=' literal     {$$ = new ook::func_decl_node(LINE, $2, $3, $5, $8, false, false); }
            | tIMPORT type tIDENTIFIER '(' fparams ')' '=' literal     {$$ = new ook::func_decl_node(LINE, $2, $3, $5, $8, true, true); }
            ;
     
fparams     : params                           { $$ =   $1; }
            |                                  { $$ = NULL; }
            ;

params      : param                            { $$ = new cdk::sequence_node(LINE, $1); }
            | params ',' param                 { $$ = new cdk::sequence_node(LINE, $3, $1); }
            ;

param       : type tIDENTIFIER                 { $$ = new ook::variable_decl_node(LINE, $1, $2, NULL, false, false, true); };


literal     : tINTEGER                         { $$ = new cdk::integer_node (LINE, $1); }
            | tDOUBLE                          { $$ = new cdk::double_node  (LINE, $1); }
            | litString                        { $$ = new cdk::string_node  (LINE, $1); }
            ;

litString   : tSTRING                          { $$ = $1; }
            | litString tSTRING                { $$ = new std::string(*$1 + *$2); delete $1; delete $2; }
            ;

instrs      : instr                            { $$ = new cdk::sequence_node(LINE, $1); }
            | instrs instr                     { $$ = new cdk::sequence_node(LINE, $2, $1); }
            ;
            
instr       : expr ';'                         { $$ = new ook::evaluation_node(LINE, $1); }
            | expr '!'                         { $$ = new ook::print_node(LINE, $1, false); }
            | expr tPRINTLN                    { $$ = new ook::print_node(LINE, $1,  true); }
            | tSTOP                            { $$ = new ook::break_node(LINE); }
            | tRETURN                          { $$ = new ook::return_node(LINE); }
            | tNEXT                            { $$ = new ook::continue_node(LINE); }
            | cond                             { $$ = $1; }
            | iter                             { $$ = $1; }
            | block                            { $$ = $1; }
            ;
     
cond        : tIF '(' expr ')' instr             { $$ = new ook::if_node(LINE, $3, $5); }
            /*| tIF '(' expr ')' instr %prec pIF   { $$ = new ook::if_else_node(LINE, $3, $5, NULL); }*/
            | tIF '(' expr ')' instr tELSE instr { $$ = new ook::if_else_node(LINE, $3, $5, $7); }
            ;
            
iter        : tWHILE '('expr ')' instr          { $$ = new ook::while_node(LINE, $3, $5); }
            ;

            
block       : '{' vardecls instrs '}'          { $$ = new ook::block_node(LINE, $2, $3); }
            | '{' vardecls '}'                 { $$ = new ook::block_node(LINE, $2, NULL); }
            | '{' instrs '}'                   { $$ = new ook::block_node(LINE, NULL, $2); }
            | '{' '}'                          { $$ = new ook::block_node(LINE, NULL, NULL); }
            ;


expr        : expr '+' expr                    { $$ = new cdk::add_node (LINE, $1, $3); }
            | expr '-' expr                    { $$ = new cdk::sub_node (LINE, $1, $3); }
            | expr '*' expr                    { $$ = new cdk::mul_node (LINE, $1, $3); }
            | expr '/' expr                    { $$ = new cdk::div_node (LINE, $1, $3); }
            | expr '%' expr                    { $$ = new cdk::mod_node (LINE, $1, $3); }
            | expr '<' expr                    { $$ = new cdk::lt_node  (LINE, $1, $3); }
            | expr '>' expr                    { $$ = new cdk::gt_node  (LINE, $1, $3); }
            | expr tGE expr                    { $$ = new cdk::ge_node  (LINE, $1, $3); }
            | expr tLE expr                    { $$ = new cdk::le_node  (LINE, $1, $3); }
            | expr tNE expr                    { $$ = new cdk::ne_node  (LINE, $1, $3); }
            | expr tEQ expr                    { $$ = new cdk::eq_node  (LINE, $1, $3); }
            | expr '&' expr                    { $$ = new ook::and_node  (LINE, $1, $3); }
            | expr '|' expr                    { $$ = new ook::or_node   (LINE, $1, $3); }
            | '+' expr      %prec pUNARY       { $$ = new ook::identity_node(LINE, $2); }
            | '-' expr      %prec pUNARY       { $$ = new cdk::neg_node(LINE, $2); }
            | '~' expr                         { $$ = new ook::not_node(LINE, $2); }
            | '@'                              { $$ = new ook::read_node(LINE); }
            | lval '=' expr                    { $$ = new ook::assignment_node(LINE, $1, $3); }
            | lval '?'                         { $$ = new ook::memory_address_node(LINE, $1); }
            | '[' expr ']'                     { $$ = new ook::memory_alloc_node(LINE, $2); }
            | '(' expr ')'                     { $$ = $2; }
            | literal                          { $$ = $1; }
            | funcall                          { $$ = $1; }
            | lval                             { $$ = new ook::rvalue_node(LINE, $1); }
            ;

lval        : tIDENTIFIER                      { $$ = new ook::simple_lvalue_node(LINE, $1); }
            | '(' expr ')' '[' expr ']'        { $$ = new ook::index_lvalue_node(LINE, $2, $5);  }
            | funcall      '[' expr ']'        { $$ = new ook::index_lvalue_node(LINE, $1, $3);  }
            | literal      '[' expr ']'        { $$ = new ook::index_lvalue_node(LINE, $1, $3);  }
            | lval         '[' expr ']'        { $$ = new ook::index_lvalue_node(LINE, new ook::rvalue_node(LINE, $1), $3);  }
            | lval '?'     '[' expr ']'        { $$ = new ook::index_lvalue_node(LINE, new ook::rvalue_node(LINE, $1), $4);  }
            ;

funcall     : tIDENTIFIER '('       ')'        { $$ = new ook::func_call_node(LINE, $1, NULL); }
            | tIDENTIFIER '(' args ')'         { $$ = new ook::func_call_node(LINE, $1,   $3); }
            ;

args        : arg                              { $$ = new cdk::sequence_node(LINE, $1); }
            | arg ',' args                     { $$ = new cdk::sequence_node(LINE, $1, $3); }
            ;

arg         : expr                             { $$ = $1;}            
            
%%
