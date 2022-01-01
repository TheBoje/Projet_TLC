%{
//extern "C" int yylex();
%}

litteral -?[0-9]+
variable [a-z]+([a-z]+|_)*

%%

BAISSER         { printf("baisser"); }
LEVER           { printf("lever"); }
CHANGER_COULEUR { printf("changer_couleur"); }

TOURNER         { printf("tourner"); }
AVANCER         { printf("avancer"); }

POUR            { printf("pour"); }
ALLANT_A        { printf("allant_a"); }
FIN_POUR        { printf("fin_pour"); }

TANT_QUE        { printf("tant_que"); }
FIN_TANT_QUE    { printf("fin_tant_que"); }

SI              { printf("si"); }
SINON           {}
FIN_SI          { printf("fin_si"); }

FAIRE           { }

LIGNE           { printf("ligne"); }
RECTANGLE       { printf("rectangle"); }

SUP_A           {}
SUP_EGAL_A      {}
INF_A           {}
INF_EGAL_A      {}
EGAL_A          {}

NOIR            { printf("(0, 0, 0)"); }
BLANC           { printf("(255, 255, 255)"); }
ROUGE           { printf("(255, 0, 0)"); }
VERT            { printf("(0, 255, 255)"); }
BLEU { }
JAUNE { }
VIOLET { }
MARRON { }


{litteral}      { printf("lit{%s}", yytext); }
{variable}      { printf("var{%s}", yytext); }

"+"             { printf("plus"); }
"-"             { printf("moins"); }
"<"             { printf("affectation"); }
";"             { printf("fin_ligne"); }

#               { printf("commentaire"); }
###             { printf("commentaire_multiligne"); }

%%

int main() {
    int res = yylex();
    return res;
}