%{
#include <iostream>
#include "parser.tab.hh"
extern "C" int yylex();
%}

litteral -?[0-9]+
variable [a-z]+([a-z]+|_)*

%%

###(.|\n)*###   { std::cout << "commentaire bloc"; }
#.*"\n"         { std::cout << "commentaire ligne "; }

BAISSER         { return DOWN; }
LEVER           { return UP; }
CHANGER_COULEUR { return CHANGECOL; }

TOURNER         { return ROTATE; }
AVANCER         { return FORWARD; }

POUR            { return FOR; }
ALLANT_A        { return TO; }
FIN_POUR        { return ENDFOR; }

TANT_QUE        { return WHILE; }
FIN_TANT_QUE    { return ENDWHILE; }

SI              { return IF; }
SINON           { return ELSE; }
FIN_SI          { return ENDIF; }

FAIRE           { return DO; }

LIGNE           { return LINE; }
RECTANGLE       { return RECTANGLE; }

NOIR            { return BLACK; }
BLANC           { return WHITE; }
ROUGE           { return RED; }
VERT            { return GREEN; }
BLEU            { return BLUE; }
JAUNE           { return YELLOW; }
VIOLET          { return PURPLE; }
MARRON          { return BROWN; }


{litteral}      { yylval.cst = atof(yytext); return CONSTANT; }
{variable}      { yylval.var = strdup(yytext); return VARIABLE; }

"<-"            { return AFFECT; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return TIMES; }
"/"             { return DIVIDE; }
";"             { return ENDLINE; }

">"             { return GT;}
">="            { return GEQ; }
"<"             { return LT; }
"<="            { return LEQ; }
"="             { return EQ; }
"&&"            { return AND; }
"||"            { return OR; }

[ \n\t]         {}

%%
