#include "change_color.hh"

clurtle::change_color::change_color(std::array<int, 3> color) :
    _color(color)
{}

clurtle::change_color::~change_color() {}

void clurtle::change_color::visit(visitor & v) const {
    return v.visit_change_color(this);
}