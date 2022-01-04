#include "clurtle.hh"

#include "change_color.hh"
#include "forward.hh"

clurtle::clurtle::clurtle() : 
    _pen_is_up(true), 
    _color({0, 0, 0})
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
    int amount = f->get_amount();
    // Déplacer de "amount"
}
