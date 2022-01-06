#include "affectation.hh"

clurtle::affectation::affectation(std::string var, expr * expr) :
    _var(var),
    _expr(expr)
{}

clurtle::affectation::~affectation() {}

void clurtle::affectation::visit(visitor & v) const {
    return v.visit_affectation(this);
}