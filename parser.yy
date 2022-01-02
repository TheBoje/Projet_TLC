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
%token FOR TO ENDFOR WHILE ENWHILE IF ELSE ENDIF DO
%token LINE RECTANGLE
%token GT GEQ LT LEQ EQ
%token BLACK WHITE RED GREEN BLUE YELLOW PURPLE BROWN
%token AFFECT PLUS MINUS ENDLINE
%token COMMENT MULTCOMMENT
%token <cst> CONSTANT
%token <var> VARIABLE

%start prog

%%

prog: {}
;

%%
