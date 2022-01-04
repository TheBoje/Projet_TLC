%{
extern "C" int yylex();

#include <iostream>
void yyerror(const char *s) { std::cerr << "ERREUR : " << s << std::endl; }

%}

%union {
    int cst;
    char* var;
}

%token DOWN UP CHANGECOL
%token ROTATE FORWARD
%token FOR TO ENDFOR WHILE ENDWHILE IF ELSE ENDIF DO
%token LINE RECTANGLE
%token GT GEQ LT LEQ EQ AND OR
%token BLACK WHITE RED GREEN BLUE YELLOW PURPLE BROWN
%token AFFECT PLUS MINUS TIMES DIVIDE ENDLINE
%token <cst> CONSTANT
%token <var> VARIABLE

%start prog

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
| expr PLUS expr    { std::cout << "+"; }
| expr TIMES expr   { std::cout << "*"; }
| expr MINUS expr   { std::cout << "-"; }
| expr DIVIDE expr  { std::cout << "/"; }
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
