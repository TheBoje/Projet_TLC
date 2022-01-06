#include "color.hh"

namespace clurtle {
    color::color(expr * r, expr * g, expr * b) : _r(r), _g(g), _b(b) {}

    color::~color() {}

    void color::visit(visitor & v) const {
        return v.visit_color(this);
    }
}