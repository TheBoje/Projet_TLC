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
    int hyp = f->get_amount();
    int x = _pos[0] + hyp * cos(_rotation * (M_1_PI / 180));
    int y = _pos[1] + hyp * sin(_rotation * (M_1_PI / 180));

    // TODO: Déplacer de "amount"
}

void clurtle::clurtle::visit_rotate(const rotate * r) {
    _rotation = (_rotation + r->get_amount()) % 360;
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

void clurtle::clurtle::visit_conditional(const conditional * c) {

}

void clurtle::clurtle::visit_while_loop(const while_loop * wl) {

}

void clurtle::clurtle::visit_for_loop(const for_loop * fl) {

}
