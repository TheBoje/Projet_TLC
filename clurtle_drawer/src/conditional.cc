#include "conditional.hh"

clurtle::conditional::conditional(expr * cond, seq_item * cons, seq_item * alt) :
    _cond(cond),
    _cons(cons),
    _alt(alt)
{}

clurtle::conditional::~conditional() {
    delete _cond;
    delete _cons;
    if (_alt != nullptr) {
        delete _alt;
    }
}

void clurtle::conditional::visit(visitor & v) const {
    v.visit_conditional(this);
}