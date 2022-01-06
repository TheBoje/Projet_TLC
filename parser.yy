%{
// extern "C" int yylex();
%}

%code requires {
    // https://stackoverflow.com/questions/34418381/how-to-reference-lex-or-parse-parameters-in-flex-rules
    #include <iostream>
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
    #include "clurtle_drawer/include/seq.hh"
    #include "clurtle_drawer/include/term.hh"
    #include "clurtle_drawer/include/up.hh"
    #include "clurtle_drawer/include/variable.hh"
    #include "clurtle_drawer/include/while_loop.hh"

    typedef struct Context { clurtle::sequence * s; } Context;

}

%union {
    int cst;
    char* var;
    clurtle::instr * instruction;
    clurtle::expr * expression;
}

%define api.pure full
%locations
%parse-param { Context* context }
%lex-param { Context* context }


%code provides {
   #define YY_DECL \
       int yylex(YYSTYPE* yylval, YYLTYPE* yyllocp, Context* context)
   YY_DECL;

   int yyerror(YYLTYPE* yyllocp, Context* context, const char* message) { std::cerr << "ERREUR : " << message << std::endl; return 1; }
}


%token DOWN UP CHANGECOL
%token ROTATE FORWARD
%token FOR TO ENDFOR WHILE ENDWHILE IF ELSE ENDIF DO
%token LINE RECTANGLE
%token GT GEQ LT LEQ EQ AND OR
%token BLACK WHITE RED GREEN BLUE YELLOW PURPLE BROWN
%token AFFECT PLUS MINUS TIMES DIVIDE ENDLINE
%token LPAR RPAR
%token <cst> CONSTANT
%token <var> VARIABLE

%left LT LEQ GT GEQ
%left PLUS MINUS
%left TIMES DIVIDE

%start prog

%type<instruction> seq affectation conditional for_loop while_loop instr
%type<expression> expr cond

%%

prog: seq { std::cout << "Entering prog" << std::endl; }
;

seq: seq line { }
| {}
;

color: BLACK    { std::cout << "C.BLACK"; }
| WHITE         { std::cout << "C.WHITE"; }
| RED           { std::cout << "C.RED"; }
| GREEN         { std::cout << "C.GREEN"; }
| BLUE          { std::cout << "C.BLUE"; }
| YELLOW        { std::cout << "C.YELLOW"; }
| PURPLE        { std::cout << "C.PURPLE"; }
| BROWN         { std::cout << "C.BROWN"; }
| CONSTANT CONSTANT CONSTANT { std::cout << "C.CUSTOM"; }
;


expr: CONSTANT      { std::cout << "constant"; }
| VARIABLE          { std::cout << "var"; }
| MINUS expr        { std::cout << "unary-"; }
| expr PLUS expr    { std::cout << "+"; }
| expr TIMES expr   { std::cout << "*"; }
| expr MINUS expr   { std::cout << "-"; }
| expr DIVIDE expr  { std::cout << "/"; }
| LPAR expr RPAR    { std::cout << "PAR"; } 
;

cond: expr GT expr  { std::cout << ">"; }
| expr GEQ expr     { std::cout << ">="; }
| expr LT expr      { std::cout << "<"; }
| expr LEQ expr     { std::cout << "<="; }
| expr EQ expr      { std::cout << "="; }
| cond AND cond     { std::cout << "&&"; }
| cond OR cond      { std::cout << "||"; }
;

affectation: VARIABLE AFFECT expr { std::cout << "var="; }
;

conditional: IF cond DO seq ENDIF { std::cout << "IF"; }
| IF cond DO seq ELSE DO seq ENDIF { std::cout << "IFELSE"; }
;

for_loop: FOR VARIABLE TO expr DO seq ENDFOR { std::cout << "FOR"; }
;

while_loop: WHILE cond DO seq ENDWHILE { std::cout << "WHILE"; }
;

control_struct: for_loop {}
| while_loop {}
| conditional {}
;

instr: DOWN             { std::cout << "DOWN"; }
| UP                    { std::cout << "UP"; }
| CHANGECOL color       { std::cout << "CHANGECOL"; }
| FORWARD expr          { std::cout << "FORWARD"; }
| ROTATE expr           { std::cout << "ROTATE"; }
| LINE expr             { std::cout << "LINE"; }
| RECTANGLE expr expr   { std::cout << "RECTANGLE"; }
| control_struct        { }
| affectation           { }
;

line: instr ENDLINE { std::cout << std::endl; }
;


%%
