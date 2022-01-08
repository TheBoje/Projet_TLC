#include "color.hh"

namespace clurtle {
    color::color(expr * r, expr * g, expr * b) : _r(r), _g(g), _b(b) {}

    color::~color() {
        delete _r;
        delete _g;
        delete _b;
    }

    void color::visit(visitor & v) const {
        return v.visit_color(this);
    }
}