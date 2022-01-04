#ifndef VARIABLE_HH
#define VARIABLE_HH

#include <string>

#include "expr.hh"

namespace clurtle {
    class variable : public expr {
        std::string _name;
        expr *      _value;
    public:
        variable();
        ~variable();

        inline std::string get_name() const { return _name; }
        inline expr * get_value() const { return _value; }

        void visit(visitor & v) const;
    };
}

#endif