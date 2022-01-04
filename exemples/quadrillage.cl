hauteur <- 10;
largeur <- 20;

POUR x ALLANT_A largeur FAIRE
    TOURNER 90;
    BAISSER;
    LIGNE hauteur;
    LEVER;
    TOURNER -90;
    AVANCER 1;
FIN_POUR;

TOURNER 180;
AVANCER largeur;
TOURNER -90;

POUR y ALLANT_A hauteur FAIRE
    TOURNER -90;
    BAISSER;
    LIGNE largeur;
    LEVER;
    TOURNER 90;
    AVANCER 1;
FIN_POUR;