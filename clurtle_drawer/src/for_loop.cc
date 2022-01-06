#include "for_loop.hh"

clurtle::for_loop::for_loop(std::string var, instr * body) :
    _var(var),
    _body(body)
{}

clurtle::for_loop::~for_loop() {}

void clurtle::for_loop::visit(visitor & v) const {
    return v.visit_for_loop(this);
}