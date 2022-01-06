#include "ope.hh"

clurtle::ope::ope(ope_symbol o, expr * left, expr * right) :
    _left(left),
    _symbol(o),
    _right(right)
{}

clurtle::ope::~ope() {}

void clurtle::ope::visit(visitor & v) const {
    return v.visit_ope(this); 
}