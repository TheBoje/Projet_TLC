#include "while_loop.hh"

clurtle::while_loop::while_loop(expr * cond, instr * body) :
    _cond(cond),
    _body(body)
{}

clurtle::while_loop::~while_loop() {}

void clurtle::while_loop::visit(visitor & v) const {
    return v.visit_while_loop(this);
}