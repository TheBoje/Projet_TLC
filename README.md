# Projet_TLC

CLurtle (Commin-Leenart-Turtle)
.cl

Liste des commandes : 

### Commandes du crayon 
- `BAISSER;` : baisse le crayon et permet l'écriture lors du déplacement de celui-ci
- `LEVER;` : lève le crayon et ne permet pas l'écriture lors du déplacement
- `CHANGER_COULEUR %couleur|R G B%;` : change la couleur RGB du crayon (soit une couleur prédéfini par les presets [couleurs](#couleurs), soit par un code RGB ie : `0 45 21`)

### Commandes du déplacement
- `AVANCER %distance%;` : avance dans la direction dans laquelle elle est tournée de `distance` unités (où `distance est un entier signé`)
- `TOURNER %degré%;` : tourne de `degré` degré(s). `degré` est un entier signé pouvant dépacer 360 ou -360 (la tortue fera plusieurs tours sur elle-même)

### Structures de contrôles
- `POUR %incr% ALLANT_A %portée% FAIRE ..... FIN_POUR;` : boucle pour prenant une variable `incr` qui sera initialisée à 0 et qui, pour chaque tour, sera incrémenté jusqu'à `portée` - 1. Le code dans le corps de la boucle sera exécuté à chaque tour.
- `TANT_QUE %condition% FAIRE ..... FIN_TANT_QUE;` : boucle exécutant le code dans son corps tant que `condition` est vraie (cf [conditions](#conditions) pour l'utilisation des conditions).
- `SI %condition% FAIRE ..... SINON FAIRE ..... FIN_SI;` ou `SI %condition% FAIRE ..... FIN_SI;` : (cf [conditions](#conditions) pour l'utilisation des conditions)

### Variables et affectations
- Les variables doivent être en minuscules. Seuls les caractères de `a` à `z` et les `_` (si ceux-ci ne sont pas placés en début de mot) sont autorisés.
- `%nom_variable% < %valeur%|%exp%` : affecte la valeur `valeur` à `nom_variable`. `valeur` peut être une expression. 

### Conditions

- `%exp1% SUP_A %exp2%` : vraie si `exp1` est strictement supérieur à `exp2`
- `%exp1% SUP_EGAL_A %exp2%` : vraie si `exp1` est supérieur ou égal à `exp2`
- `%exp1% INF_A %exp2%` : vraie si `exp1` est inférieur à `exp2`
- `%exp1% INF_EGAL_A %exp2%` : vraie si `exp1` est inférieur ou égal à `exp2`
- `%exp1% EGAL_A %exp2%` : vraie si `exp1` est égal à `exp2`

### Couleurs 

- `NOIR` : (0, 0, 0)
- `BLANC` : (255, 255, 255)
- `ROUGE` : (255, 0, 0)
- `VERT` : (0, 255, 0)
- `BLEU` : (0, 0, 255)
- `JAUNE`
- `VIOLET`
- `MARRON`