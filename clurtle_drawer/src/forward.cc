#include "forward.hh"

clurtle::forward::forward(int amount) :
    _amount(amount)
{}

clurtle::forward::~forward() {};

void clurtle::forward::visit(visitor & v) const {
    return v.visit_forward(this);
}