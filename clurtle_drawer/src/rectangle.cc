#include "rectangle.hh"

clurtle::rectangle::rectangle(expr * length, expr * width) :
    _length(length),
    _width(width)
{}

clurtle::rectangle::~rectangle() {
    delete _length;
    delete _width;
}

void clurtle::rectangle::visit(visitor & v) const {
    return v.visit_rectangle(this);
}