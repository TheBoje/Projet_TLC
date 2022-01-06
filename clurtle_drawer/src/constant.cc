#include "constant.hh"

namespace clurtle {
    constant::constant(int value) : _value(value) {}

    constant::~constant() {}

    void constant::visit(visitor & v) const {
        return v.visit_constant(this);
    }
} 