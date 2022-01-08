#include "for_loop.hh"

clurtle::for_loop::for_loop(variable * var, expr * from, expr * to, seq_item * body) :
    _var(var),
    _from(from),
    _to(to),
    _body(body)
{}

clurtle::for_loop::~for_loop() {
    delete _var;
    delete _from;
    delete _to;
    delete _body;
}

void clurtle::for_loop::visit(visitor & v) const {
    return v.visit_for_loop(this);
}