%{
extern "C" int yylex();

#include <iostream>
void yyerror(const char *s) { std::cerr << "ERREUR : " << s << std::endl; }

%}

%start prog

%%

prog: {}
;

%%
