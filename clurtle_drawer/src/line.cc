#include "line.hh"

clurtle::line::line(expr * length) :
    _length(length)
{}

clurtle::line::~line() {}

void clurtle::line::visit(visitor & v) const {
    return v.visit_line(this);
}