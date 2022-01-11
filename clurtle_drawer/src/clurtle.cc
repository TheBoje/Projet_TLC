#include "clurtle.hh"

#include <math.h>
#include <iostream>

#include "change_color.hh"
#include "forward.hh"
#include "rotate.hh"
#include "line.hh"
#include "rectangle.hh"
#include "conditional.hh"
#include "while_loop.hh"
#include "for_loop.hh"
#include "ope.hh"
#include "constant.hh"
#include "variable.hh"
#include "affectation.hh"
#include "seq.hh"
#include "color.hh"

/**
 * @brief Construit une clurtle, initialise aussi l'image de taille sizex/sizey 
 * avec un fond blanc. 
 * Positionne la clurtle au centre de l'image avec le crayon est levé regardant vers l'EST.
 * 
 * @param sizex 
 * @param sizey 
 */
clurtle::clurtle::clurtle(int sizex, int sizey) : 
    _pen_is_up(true), 
    _color{0, 0, 0},
    _pos({(double)(sizex / 2), (double)(sizey / 2)}),
    _rotation(0.),
    _img(cimg_library::CImg<unsigned char>(sizex, sizey, 1, 3))
{
    _img.fill(255);
}

/**
 * @brief Détruit la clurtle. Va sauvegarder l'image au format ... 
 * et va l'afficher dans une fenêtre, pour la fermer, il faut appuyer sur Q.
 * 
 */
clurtle::clurtle::~clurtle() {
    cimg_library::CImgDisplay disp;
    disp.display(_img);


    _img.save_bmp("toto.bmp");


    while (!disp.is_closed()) 
    {
        // boucle des evenements
        if (disp.key() == cimg_library::cimg::keyQ)
        disp.close();
        disp.wait();
    }
}

/**
 * @brief Lève le crayon ce qui empèchera le dessin 
 * lors du déplacement de la clurtle.
 * 
 * @param u 
 */
void clurtle::clurtle::visit_up(const up * u) {
    _pen_is_up = true;
    (void)u; // Suppress unused-parameter warning
}

/**
 * @brief Fonctionnement inverse de visit_up
 * 
 * @param d 
 */
void clurtle::clurtle::visit_down(const down * d) {
    _pen_is_up = false;
    (void)d; // Suppress unused-parameter warning
}

void clurtle::clurtle::visit_change_color(const change_color * cc) {
    cc->get_color()->visit(*this);
}

/**
 * @brief Visite les expressions des trois composantes RGB pour les 
 * appliquer à la couleur du crayon. A noter que la bibliothèque CImg.h 
 * utilise l'espace BGR.
 * 
 * @param c 
 */
void clurtle::clurtle::visit_color(const color * c) {
    c->get_r()->visit(*this);
    c->get_g()->visit(*this);
    c->get_b()->visit(*this);

    char r = get_last_double();
    char g = get_last_double();
    char b = get_last_double();

    _color[2] = r;
    _color[1] = g;
    _color[0] = b;
}

/**
 * @brief Avance la clurtle de x distance se trouvant dans la pile 
 * après visite de l'expression. Le calcul du vecteur directeur se 
 * fait par trigonométrie basique. A noter qu'on utilise les double pour 
 * la position et la rotation afin d'être plus précis. Les entiers faisaient 
 * des arrondis trop flagrants.
 * Lors de sont déplacement, la clurtle va tracer son segment de déplacement
 * si son crayon est baissé.
 * 
 * @param f 
 */
void clurtle::clurtle::visit_forward(const forward * f) {
    f->get_amount()->visit(*this);
    double hyp = get_last_double();

    double x = _pos[0] + hyp * cos(_rotation * (M_PI / 180));
    double y = _pos[1] + hyp * sin(_rotation * (M_PI / 180));

    if(!_pen_is_up)
    {
        _img.draw_line(_pos[0], _pos[1], x, y, _color);

    }

    _pos[0] = x;
    _pos[1] = y;
}

/**
 * @brief Va effectuer une rotation de la clurtle.
 * On prend le modulo de la nouvelle rotation afin de rester
 * entre 0 et 360 degrés.
 * 
 * @param r 
 */
void clurtle::clurtle::visit_rotate(const rotate * r) {
    r->get_amount()->visit(*this);
    
    double rot = get_last_double();

    _rotation = std::fmod(_rotation + rot,  360);
}

/**
 * @brief On trace une ligne dans le sens du regard de la clurtle 
 * comme forward() même si le crayon est debout. 
 * Cependant ici, nous ne déplaçons pas la clurtle.
 * 
 * @param l 
 */
void clurtle::clurtle::visit_line(const line * l) {
    l->get_length()->visit(*this);
    double length = get_last_double();

    double x = _pos[0] + length * cos(_rotation * (M_PI / 180));
    double y = _pos[1] + length * sin(_rotation * (M_PI / 180));

    _img.draw_line(_pos[0], _pos[1], x, y, _color);
}

/**
 * @brief Comme line() on trace un rectangle dans le sens du regard
 * de la clurtle sans se soucier de l'état du crayon.
 * 
 * @param r 
 */
void clurtle::clurtle::visit_rectangle(const rectangle * r) {
    r->get_length()->visit(*this);
    double length = get_last_double();
    r->get_width()->visit(*this);
    double width = get_last_double();

    for(int i = 0; i < 4; i++) 
    {
        int x = _pos[0] + (i % 2 == 0 ? length : width) * cos(_rotation * (M_PI / 180));
        int y = _pos[1] + (i % 2 == 0 ? length : width) * sin(_rotation * (M_PI / 180));

        _img.draw_line(_pos[0], _pos[1], x, y, _color);

        _pos[0] = x;
        _pos[1] = y;

        _rotation = std::fmod(_rotation + 90,  360);        
    }
}

/**
 * @brief Permet de calculer les valeurs des expressions.
 * Il y a trois types d'opérateurs :
 * les opérateurs sur les double, les bool et l'opérateur NOT sur
 * les bool. Les résultats sont soit placé dans la pile correspondante.
 * 
 * @param o 
 */
void clurtle::clurtle::visit_ope(const ope * o) {
    ope_symbol ope = o->get_symbol();
    
    o->get_left()->visit(*this); // not **this ?
    o->get_right()->visit(*this);
    
    int size = _stack.size();
    int sb_size = _stack_bool.size();

    if(ope != OP_AND && ope != OP_OR && size >= 2)
    {
        double a = _stack[size - 1];
        double b = _stack[size - 2];

        _stack.pop_back();
        _stack.pop_back();

        switch (ope)
        {
        case OP_PLUS:
            _stack.push_back(a + b);
            break;

        case OP_MINUS:
            _stack.push_back(a - b);
            break;

        case OP_TIMES:
            _stack.push_back(a * b);
            break;

        case OP_DIVIDE:
            _stack.push_back(a / b);
            break;

        case OP_GT:
            _stack_bool.push_back(a > b);
            break;
        
        case OP_GEQ:
            _stack_bool.push_back(a >= b);
            break;

        case OP_LT:
            _stack_bool.push_back(a < b);
            break;
        
        case OP_LEQ:
            _stack_bool.push_back(a <= b);
            break;
        
        case OP_EQ:
            _stack_bool.push_back(a == b);
            break;

        default:
            break;
        }
    }
    else if((ope == OP_AND || ope == OP_OR) && sb_size >= 2)
    {
        bool a = _stack_bool[sb_size - 1];
        bool b = _stack_bool[sb_size - 2];

        _stack_bool.pop_back();
        _stack_bool.pop_back();

        switch (ope)
        {
        case OP_AND:
            _stack_bool.push_back(a && b);
            break;
        
        case OP_OR:
            _stack_bool.push_back(a || b);
            break;

        default:
            break;
        }
    }
    else if(ope == OP_NOT && sb_size >= 1)
    {
        _stack_bool[sb_size - 1] = !_stack_bool[sb_size - 1];
    }
    
}

/**
 * @brief Visite d'une condition SI. 
 * 
 * @param c 
 */
void clurtle::clurtle::visit_conditional(const conditional * c) {
    c->get_cond()->visit(*this);
    
    bool cond = get_last_bool();

    if(cond) 
    {
        c->get_cons()->visit(*this);
    }
    else
    {
        c->get_alt()->visit(*this);
    }
}

/**
 * @brief Visite d'une boucle tant que. On recalcule la condition à chaque itération
 * de la boucle pour voir l'état de celle-ci ce qui peut entraîner un plus long
 * temps d'exécution, surtout si la condition contient beaucoup de calculs.
 * 
 * @param wl 
 */
void clurtle::clurtle::visit_while_loop(const while_loop * wl) {
    wl->get_cond()->visit(*this);
    bool res = get_last_bool();

    while(res) {
        wl->get_body()->visit(*this);
        wl->get_cond()->visit(*this);
        res = get_last_bool();
    }
}

/**
 * @brief Visite d'une boucle pour. On stocke la variable d'incrémentation
 * dans un dictionnaire à part afin d'y empếcher son affectation.
 * 
 * @param fl 
 */
void clurtle::clurtle::visit_for_loop(const for_loop * fl) {
    std::string incr = fl->get_var()->get_name();
    _it_variables[incr] = 0;

    fl->get_to()->visit(*this);
    int to = get_last_double();

    for(int i = 0; i < to; i++)
    {
        fl->get_body()->visit(*this);
    }

    _it_variables.erase(incr);
}

/**
 * @brief Place la valeur de la consante dans la pile.
 * A noter que nous n'avons pas de constante booléenne.
 * @param c 
 */
void clurtle::clurtle::visit_constant(const constant * c) {
    _stack.push_back(c->get_value());
}

/**
 * @brief On regarde dans les deux piles pour récupérer la
 * valeur de la bonne variable.
 * 
 * @param v 
 */
void clurtle::clurtle::visit_variable(const variable * v) {
    
    std::string var_name = v->get_name();

    try
    {
        _stack.push_back(_it_variables.at(var_name));
    }
    catch(const std::out_of_range& e)
    {
        try
        {
            _stack.push_back(_variables.at(var_name));
        }
        catch(const std::out_of_range& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}

/**
 * @brief On vérifie si la varibale n'existe pas en tant que variable 
 * d'itération. Si ce n'est pas le cas, on affecte la valeur à une nouvelle variable.
 * 
 * @param a 
 */
void clurtle::clurtle::visit_affectation(const affectation * a) {
    a->get_expr()->visit(*this);
    std::string var_name = a->get_var()->get_name();
        
    try
    {
        _it_variables.at(var_name);
    }
    catch(const std::out_of_range& e)
    {
        _variables[var_name] = get_last_double();
    }
}

/**
 * @brief On exécute l'instruction courante en la visitant puis on passe 
 * à la suivante.
 * 
 * @param s 
 */
void clurtle::clurtle::visit_sequence(const sequence * s) {
    seq_item * t = s->get_first();
    while(t != nullptr) 
    {
        t->get_inst()->visit(*this);
        t = t->get_next();
    }
}

/**
 * @brief On parcours toutes les séquences.
 * 
 * @param si 
 */
void clurtle::clurtle::visit_seq_item(const seq_item * si) {
    if (si != NULL) 
    {
        if (si->get_inst() != NULL) 
        {
            si->get_inst()->visit(*this);
            if (si->get_next() != NULL) 
            {
                si->get_next()->visit(*this);
            } 
        }
    }
}

