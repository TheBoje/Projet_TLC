#ifndef CLURTLE_CPP_HH
#define CLURTLE_CPP_HH

#include <array>
#include <iostream>
#include <fstream>
#include <vector>
#include "visitor.hh"
#include "expr.hh"

namespace clurtle {

    /**
     * Seconde approche pour l'exploitation de l'arbre généré par yyparse().
     * Cette approche consiste à traduire le code CLurtle en CPP. Ca implique que CLurtle_cpp
     * attends un fichier .cl en entrée, et donne un fichier .cpp en sortie, qu'il faut compiler
     * avant de lancer. Cette approche a plutôt été faite pour explorer le fonctionnement du système.
     * Note: ce code a 1 bug déjà connu (et qui n'a pas été résolu à temps). Les variables déclarées
     * dans les blocks (POUR, SI, TANT_QUE) ne sont pas détectés comme inconnus en dehors du bloc.
     * Si on fait appelle à une variable déclarée dans un bloc en dehors de ce dernier, alors il y
     * aura une erreur de compilation pour le résultat de cpp -> code machine (et non cl -> cpp). Il
     * faudrait compter les variables déclarés dans un bloc et les interdires ultérieurement /
     * demander une nouvelle déclaration ou quelque chose comme ca. Bref, ce truc marche pas.
     * 
     * Sinon le principe est simple, on créé un fichier .cpp, on écrit dans ce dernier un header qui
     * contient des fonction prédéfinies (line(), rectangle(), etc), voir `clurtle_cpp.header`.
     * Ensuite on visite tout l'arbre, à chaque visite pertinante, on écrit dans le .cpp
     * l'équivalent. Une fois tout l'arbre visité, on ajoute un footer au .cpp, voir
     * `clurtle_cpp.footer`. Enfin, il suffit de compiler le .cpp et de lancer l'executable.
     * 
     * le fichier de retour .cpp ressemble donc a ca : 
     * - contenu de `clurtle_cpp.header`
     * - code cpp généré dans `clurtle_cpp.cc` à partir de l'arbre
     * - contenu de `clurtle_cpp.footer`
     * 
     * Afin de ne pas passer des semaines sur ce code, on a utilisé quelques moyens pas des plus
     * élégants, mais ca se limite à la manière de visiter chaque noeud et non pas notre approche du
     * lexer / parser. À noter que l'approche faite dans `clurtle.cc` fait appel à plus de notions
     * de compilation, et le résultat est plus stable.
    */
    class clurtle_cpp : public visitor {
        std::ofstream _file_out;    // Résultat de la compilation
        std::ifstream _file_header; // Header à écrire au début de `_file_out`
        std::ifstream _file_footer; // Footer à écrire à la fin de `_file_out`
        std::vector<std::string> _initialized;  // Liste des noms de variable déjà initialisées - que l`on conserve pour ne pas déclarer 2 fois une variable
        std::vector<std::string> _dont_use;     // Liste des noms de variable de boucle, dont il est interdit d'affecter une valeur
        int _indent;    // Nombre de cran d'indentation pour rendre `_file_out` un peu plus lisible 
        
    public:
        clurtle_cpp(std::string filename);
        ~clurtle_cpp();

        void visit_up(const up * u);
        void visit_down(const down * d);
        void visit_change_color(const change_color * cc);
        void visit_color(const color * c);
        void visit_forward(const forward * f);
        void visit_rotate(const rotate * r);
        void visit_line(const line * l);
        void visit_rectangle(const rectangle * r);
        void visit_conditional(const conditional * c);
        void visit_while_loop(const while_loop * wl);
        void visit_for_loop(const for_loop * fl);
        void visit_ope(const ope * o);
        void visit_constant(const constant * c);
        void visit_variable(const variable * v);
        void visit_affectation(const affectation * a);
        void visit_sequence(const sequence * s);
        void visit_seq_item(const seq_item * si);
    };
}

#endif