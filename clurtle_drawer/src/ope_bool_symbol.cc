#include "ope_bool.hh"

clurtle::ope_bool::ope_bool(ope_bool_symbol o, expr * left, expr * right) :
    _symbol(o),
    _left(left),
    _right(right)
{}

clurtle::ope_bool::~ope_bool() {}

void clurtle::ope_bool::visit(visitor & v) const {
    return v.visit_ope_bool(this); 
}