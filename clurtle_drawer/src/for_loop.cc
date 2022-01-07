#include "for_loop.hh"

clurtle::for_loop::for_loop(variable * var, expr * to, seq_item * body) :
    _var(var),
    _to(to),
    _body(body)
{}

clurtle::for_loop::~for_loop() {}

void clurtle::for_loop::visit(visitor & v) const {
    return v.visit_for_loop(this);
}