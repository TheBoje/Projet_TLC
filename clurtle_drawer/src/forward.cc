#include "forward.hh"

clurtle::forward::forward(expr * amount) :
    _amount(amount)
{}

clurtle::forward::~forward() {
    delete _amount;
};

void clurtle::forward::visit(visitor & v) const {
    return v.visit_forward(this);
}