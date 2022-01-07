%{
#include <iostream>
#include <string>
extern "C" int yylex();

#include "clurtle_drawer/include/seq.hh"
extern "C" void yyerror(clurtle::sequence ** res, const char* message);

%}

%code requires {
    // https://stackoverflow.com/questions/34418381/how-to-reference-lex-or-parse-parameters-in-flex-rules
    #include "clurtle_drawer/include/affectation.hh"
    #include "clurtle_drawer/include/change_color.hh"
    #include "clurtle_drawer/include/color.hh"
    #include "clurtle_drawer/include/conditional.hh"
    #include "clurtle_drawer/include/constant.hh"
    #include "clurtle_drawer/include/down.hh"
    #include "clurtle_drawer/include/expr.hh"
    #include "clurtle_drawer/include/for_loop.hh"
    #include "clurtle_drawer/include/forward.hh"
    #include "clurtle_drawer/include/instr.hh"
    #include "clurtle_drawer/include/line.hh"
    #include "clurtle_drawer/include/ope.hh"
    #include "clurtle_drawer/include/rectangle.hh"
    #include "clurtle_drawer/include/rotate.hh"
    #include "clurtle_drawer/include/term.hh"
    #include "clurtle_drawer/include/up.hh"
    #include "clurtle_drawer/include/variable.hh"
    #include "clurtle_drawer/include/while_loop.hh"

    using namespace clurtle;

}

%union {
    int cst;
    char* var;
    clurtle::instr * instruction;
    clurtle::expr * expression;
    clurtle::seq_item * seq_item;
    clurtle::color * color;
    clurtle::sequence * sequence;
}

%parse-param { clurtle::sequence ** res }


%code provides {
    int yyparse(clurtle::sequence ** res);
}


%token DOWN UP CHANGECOL
%token ROTATE FORWARD
%token FOR TO ENDFOR WHILE ENDWHILE IF ELSE ENDIF DO
%token LINE RECTANGLE
%token GT GEQ LT LEQ EQ AND OR NOT
%token BLACK WHITE RED GREEN BLUE YELLOW PURPLE CYAN
%token AFFECT PLUS MINUS TIMES DIVIDE ENDLINE
%token LPAR RPAR
%token <cst> CONSTANT
%token <var> VARIABLE

%left LT LEQ GT GEQ
%left PLUS MINUS
%left TIMES DIVIDE

%start prog

%type<sequence> prog
%type<color> color
%type<seq_item> seq
%type<instruction> affectation conditional for_loop while_loop instr control_struct line
%type<expression> expr cond

%%

prog: seq { *res = new sequence($1); } 
;

seq: line seq { $$ = new seq_item($1, $2); }
| { $$ = nullptr; }
;

color: BLACK     { $$ = new color(new constant(  0), new constant(  0), new constant(  0)); }
| WHITE          { $$ = new color(new constant(255), new constant(255), new constant(255)); }
| RED            { $$ = new color(new constant(255), new constant(  0), new constant(  0)); }
| GREEN          { $$ = new color(new constant(  0), new constant(255), new constant(  0)); }
| BLUE           { $$ = new color(new constant(  0), new constant(  0), new constant(255)); }
| YELLOW         { $$ = new color(new constant(255), new constant(255), new constant(  0)); }
| PURPLE         { $$ = new color(new constant(255), new constant(  0), new constant(255)); }
| CYAN           { $$ = new color(new constant(  0), new constant(255), new constant(255)); }
| expr expr expr { $$ = new color($1, $2, $3); }
;


expr: CONSTANT      { $$ = new constant(yylval.cst); }
| VARIABLE          { $$ = new variable($1); }
| expr PLUS expr    { $$ = new ope(OP_PLUS, $1, $3); }
| expr TIMES expr   { $$ = new ope(OP_TIMES, $1, $3); }
| expr MINUS expr   { $$ = new ope(OP_MINUS, $1, $3); }
| expr DIVIDE expr  { $$ = new ope(OP_DIVIDE, $1, $3); }
| LPAR expr RPAR    { $$ = $2; } 
;

cond: expr GT expr  { $$ = new ope(OP_GT, $1, $3); }
| expr GEQ expr     { $$ = new ope(OP_GEQ, $1, $3); }
| expr LT expr      { $$ = new ope(OP_LT, $1, $3); }
| expr LEQ expr     { $$ = new ope(OP_LEQ, $1, $3); }
| expr EQ expr      { $$ = new ope(OP_EQ, $1, $3); }
| cond AND cond     { $$ = new ope(OP_AND, $1, $3); }
| cond OR cond      { $$ = new ope(OP_OR, $1, $3); }
| NOT cond          { $$ = new ope(OP_NOT, $2, nullptr); }
;

affectation: VARIABLE AFFECT expr { $$ = new affectation(new variable($1), $3); }
;

conditional: IF cond DO seq ENDIF { $$ = new conditional($2, $4); }
| IF cond DO seq ELSE DO seq ENDIF { $$ = new conditional($2, $4, $7); }
;

for_loop: FOR VARIABLE TO expr DO seq ENDFOR { $$ = new for_loop(new variable($2), $4, $6); }
;

while_loop: WHILE cond DO seq ENDWHILE { $$ = new while_loop($2, $4); }
;

control_struct: for_loop { $$ = $1; }
| while_loop { $$ = $1; }
| conditional { $$ = $1; }
;

instr: DOWN             { $$ = new down(); }
| UP                    { $$ = new up(); }
| CHANGECOL color       { $$ = new change_color($2); }
| FORWARD expr          { $$ = new forward($2); }
| ROTATE expr           { $$ = new rotate($2); }
| LINE expr             { $$ = new line($2); }
| RECTANGLE expr expr   { $$ = new rectangle($2, $3); }
| control_struct        { $$ = $1; }
| affectation           { $$ = $1; }
;

line: instr ENDLINE { $$ = $1; }
;


%%

void yyerror(clurtle::sequence ** res, const char* message) { std::cerr << "ERREUR : " << message << std::endl; }
