#include "change_color.hh"

clurtle::change_color::change_color(color * color) :
    _color(color)
{}

clurtle::change_color::~change_color() {
    delete _color;
}

void clurtle::change_color::visit(visitor & v) const {
    return v.visit_change_color(this);
}