#include "rotate.hh"

clurtle::rotate::rotate(expr * amount) :
    _amount(amount)
{}

clurtle::rotate::~rotate() {}

void clurtle::rotate::visit(visitor & v) const {
    return v.visit_rotate(this);
}