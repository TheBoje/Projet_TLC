#include "clurtle.hh"

#include <math.h>

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
#include "ope_bool.hh"

clurtle::clurtle::clurtle() : 
    _pen_is_up(true), 
    _color({0, 0, 0}),
    _pos({0, 0}),
    _rotation(0)
{} 

void clurtle::clurtle::visit_up(const up * u) {
    _pen_is_up = true;
}

void clurtle::clurtle::visit_down(const down * d) {
    _pen_is_up = false;
}

void clurtle::clurtle::visit_change_color(const change_color * cc) {
    _color = cc->get_color();
}

void clurtle::clurtle::visit_forward(const forward * f) {
    f->get_amount()->visit(this);
    
    int hyp = _stack[0]; _stack.pop_back();

    int x = _pos[0] + hyp * cos(_rotation * (M_1_PI / 180));
    int y = _pos[1] + hyp * sin(_rotation * (M_1_PI / 180));

    // TODO: Déplacer de "amount"
}

void clurtle::clurtle::visit_rotate(const rotate * r) {
    r->get_amount()->visit(this);
    
    int rot = _stack[0]; _stack.pop_back();

    _rotation = (_rotation + rot) % 360;
    // TODO: tourne la tortue de amount degré
}

void clurtle::clurtle::visit_line(const line * l) {
    int length = l->get_length();
    // TODO: dessine une ligne sans bouger la tortue
}

void clurtle::clurtle::visit_rectangle(const rectangle * r) {
    int length = r->get_length();
    int width = r->get_width();
    // TODO: dessine un rectangle
}


void clurtle::clurtle::visit_ope(const ope * o) {
    ope_symbol ope = o->get_symbol();
    
    o->get_left()->visit(this); // not *this ?
    o->get_right()->visit(this);
    
    int size = _stack.size();
    if(size >= 2)
    {
        int a = _stack[size - 1];
        int b = _stack[size - 2];

        _stack.pop_back();
        _stack.pop_back();

        switch (ope)
        {
        case PLUS:
            _stack.push_back(a + b);
            break;

        case MINUS:
            _stack.push_back(a - b);
            break;

        case TIMES:
            _stack.push_back(a * b);
            break;

        case DIVIDE:
            _stack.push_back(a / b);
            break;
        
        default:
            break;
        }
    }
    
}

void clurtle::clurtle::visit_conditional(const conditional * c) {

}

void clurtle::clurtle::visit_while_loop(const while_loop * wl) {

}

void clurtle::clurtle::visit_for_loop(const for_loop * fl) {

}

void clurtle::clurtle::visit_constant(const constant * c) {
    _stack.push_back(c->get_value());
}

void clurtle::clurtle::visit_ope_bool(const ope_bool * o) {

}