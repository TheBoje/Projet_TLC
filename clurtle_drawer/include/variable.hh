#ifndef VARIABLE_HH
#define VARIABLE_HH

#include <string>

#include "expr.hh"

namespace clurtle {
    class variable : public expr {
        std::string _name;
    public:
        variable(std::string name);
        ~variable();

        inline std::string get_name() const { return _name; }

        void visit(visitor & v) const;
    };
}

#endif