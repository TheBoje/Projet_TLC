#include "rectangle.hh"

clurtle::rectangle::rectangle(expr * length, expr * width) :
    _length(length),
    _width(width)
{}

clurtle::rectangle::~rectangle() {}

void clurtle::rectangle::visit(visitor & v) const {
    return v.visit_rectangle(this);
}