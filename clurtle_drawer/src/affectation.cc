#include "affectation.hh"

clurtle::affectation::affectation(variable * var, expr * expr) : 
    _var(var),
    _expr(expr)
{}

clurtle::affectation::~affectation() {
    delete _var;
    delete _expr;
}

void clurtle::affectation::visit(visitor & v) const {
    return v.visit_affectation(this);
}