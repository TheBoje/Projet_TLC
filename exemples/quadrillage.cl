hauteur <- 10;
largeur <- 10;
step <- 10;

POUR x DE 0 ALLANT_A largeur + 1 FAIRE
    TOURNER 90;
    BAISSER;
    LIGNE hauteur * step;
    LEVER;
    TOURNER -90;
    AVANCER step;
FIN_POUR;

TOURNER 180;
AVANCER largeur * step + largeur;
TOURNER -90;

POUR y DE 0 ALLANT_A hauteur + 1 FAIRE
    TOURNER -90;
    BAISSER;
    LIGNE largeur * step;
    LEVER;
    TOURNER 90;
    AVANCER step;
FIN_POUR;