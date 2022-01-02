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
%token COMMENT MULTCOMMENT
%token <cst> CONSTANT
%token <var> VARIABLE

%start prog

%%

prog: line prog {}
| line {}
;

color: BLACK {}
| WHITE {}
| RED {}
| GREEN {}
| BLUE {}
| YELLOW {}
| PURPLE {}
| BROWN {}
| CONSTANT CONSTANT CONSTANT {}
;


expr: CONSTANT {}
| VARIABLE {}
| expr PLUS expr {}
| expr TIMES expr {}
| expr MINUS expr {}
| expr DIVIDE expr {}
;

cond: expr GT expr {}
| expr GEQ expr {}
| expr LT expr {}
| expr LEQ expr {}
| expr EQ expr {}
| cond AND cond {}
| cond OR cond {}
;

affectation: VARIABLE AFFECT expr {}
;

conditional: IF cond DO prog ENDIF {}
| IF cond DO prog ELSE DO prog ENDIF {}
;

for_loop: FOR VARIABLE TO expr DO prog ENDFOR {}
;

while_loop: WHILE cond DO prog ENDWHILE{}
;

control_struct: for_loop {}
| while_loop {}
| conditional {}
;

instr: DOWN {}
| UP {}
| CHANGECOL color {}
| FORWARD CONSTANT {}
| ROTATE CONSTANT {}
| control_struct {}
;


line: instr ENDLINE {}
;


%%
