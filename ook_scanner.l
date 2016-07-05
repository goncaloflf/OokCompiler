%option c++ yyclass="ook_scanner" outfile="ook_scanner.cpp"
%option stack noyywrap yylineno 8bit
%{ 
/* $Id: ook_scanner.l,v 1.2 2016/07/01 00:22:52 ist178596 Exp $ */
// make relevant includes before including the parser's tab file
#include <string>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include "ook_scanner.h"
#include "ook_parser.tab.h"

// don't change this
#define yyerror LexerError
%}
ALPHA                         [a-zA-Z]
ALPHANUM                      [a-zA-Z0-9]
HEX                           [0-9a-fA-F]

IDENTIFIER                    ({ALPHA}|_)({ALPHANUM}|_)*

INT_DEC                       0|[1-9][0-9]*
INT_HEX                       "0x"{HEX}*[1-9a-fA-F]{HEX}*

FLOAT_DEC_1                   [0-9]*\.[0-9]+([eE][-+]?[0-9]+)?
FLOAT_DEC_2                   [0-9]+\.[0-9]*([eE][-+]?[0-9]+)?
FLOAT_DEC_3                   [0-9]+([eE][-+]?[0-9]+)
FLOAT_DEC                     {FLOAT_DEC_1}|{FLOAT_DEC_2}|{FLOAT_DEC_3}

WHITESPACE                    [ \t\n\r]


%x X_STRING X_COMMENT X_STR_ESCAPED X_IGNORE
%%

"--".*                 ; /* ignore comments */

">="                   return tGE; 
"<="                   return tLE; 
"=="                   return tEQ; 
"!="                   return tNE; 

"while"                return tWHILE; 
"if"                   return tIF; 
"else"                 return tELSE; 
"print"                return tPRINT; 
"read"                 return tREAD; 
"begin"                return tBEGIN; 
"end"                  return tEND;
"public"               return tPUBLIC;
"import"               return tIMPORT;
"next"                 return tNEXT;
"stop"                 return tSTOP;
"return"               return tRETURN;
"null"                 return tNULL;
"int"                  return tINTDECL;
"float"                return tDOUBLEDECL;
"string"               return tSTRINGDECL;
"pointer"              return tPOINTERDECL;
"void"                 return tVOID;
"!!"                   return tPRINTLN;

{IDENTIFIER}                  yylval.s = new std::string(yytext); return tIDENTIFIER;


\"                            yy_push_state(X_STRING); yylval.s = new std::string("");
<X_STRING>\"                  yy_pop_state(); return tSTRING;
<X_STRING>\\                  yy_push_state(X_STR_ESCAPED);
<X_STRING>.                   *yylval.s += yytext;
<X_STRING>\n                  yyerror("newline in string");

<X_STR_ESCAPED>t			        { yy_pop_state(); *yylval.s += std::string(1,9); }
<X_STR_ESCAPED>r			        { yy_pop_state(); *yylval.s += std::string(1,13); }
<X_STR_ESCAPED>n			        { yy_pop_state(); *yylval.s += std::string(1,10); }
<X_STR_ESCAPED>[\"\\]	        { yy_pop_state(); *yylval.s += std::string(1,(int)*yytext); }
<X_STR_ESCAPED>{HEX}{1,2}     { yy_pop_state(); *yylval.s += std::string(1,strtol(yytext, nullptr, 16)); }
<X_STR_ESCAPED>.|\n			      yyerror("Invalid special character");


"/*"                          yy_push_state(X_COMMENT);
<X_COMMENT>"/*"               yy_push_state(X_COMMENT);
<X_COMMENT>"*/"               yy_pop_state();
<X_COMMENT>.|\n               ;

"//".*$                       ;

{FLOAT_DEC}                   { yylval.d = strtod(yytext, nullptr); if(errno == ERANGE) yyerror("Overflow ocurred!"); return tDOUBLE; }
{INT_HEX}                     { yylval.i = strtol(yytext, nullptr, 16); if(errno == ERANGE) yyerror("Overflow ocurred!"); return tINTEGER; }
{INT_DEC}                     { yylval.i = strtol(yytext, nullptr, 10); if(errno == ERANGE) yyerror("Overflow ocurred!"); return tINTEGER; }
0[0-9]+                       yyerror("Malformed number!");

[ \t\n]+               ; /* ignore whitespace */

.                      yyerror("Unknown character");

%%
// Very, very dirty hack: flex is a mess generating C++ scanners.
int ook_scanner::yywrap() { return 1; }
