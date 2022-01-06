#include "variable.hh"

namespace clurtle {
    variable::variable(std::string name) : _name(name) {}

    variable::~variable() {}

    void variable::visit(visitor & v) const {
        return v.visit_variable(this);
    }
}