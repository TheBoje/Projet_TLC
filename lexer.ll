%{
//extern "C" int yylex();
#include "parser.tab.hh"
%}

litteral -?[0-9]+
variable [a-z]+([a-z]+|_)*

%%

BAISSER         { return DOWN; }
LEVER           { return UP; }
CHANGER_COULEUR { return CHANGEGOL; }

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

SUP_A           { return GT;}
SUP_EGAL_A      { return GEQ; }
INF_A           { return LT; }
INF_EGAL_A      { return LEQ; }
EGAL_A          { return EQ; }

NOIR            { return BLACK; }
BLANC           { return WHITE; }
ROUGE           { return RED; }
VERT            { return GREEN; }
BLEU            { return BLUE; }
JAUNE           { return YELLOW; }
VIOLET          { return PURPLE; }
MARRON          { return BROWN; }


{litteral}      { yyval.cst = atof(yytext); return CONSTANT; }
{variable}      { yyval.var = strdup(yytext); return VARIABLE; }

"+"             { return PLUS; }
"-"             { return MINUS; }
"<"             { return AFFECT; }
";"             { return ENDLINE; }

#               { return COMMENT; }
###             { return MULTCOMMENT; }

%%

int main() {
    int res = yylex();
    return res;
}