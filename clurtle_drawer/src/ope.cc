#include "ope.hh"

clurtle::ope::ope(ope_symbol o, expr * left, expr * right) :
    _symbol(o),
    _left(left),
    _right(right)
{}

clurtle::ope::~ope() {}

void clurtle::ope::visit(visitor & v) const {
    return v.visit_ope(this); 
}