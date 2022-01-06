#ifndef AFFECTATION_HH
#define AFFECTATION_HH

#include <string>

#include "instr.hh"
#include "expr.hh"

namespace clurtle {
    class affectation : public instr {
        variable *   _var;
        expr *      _expr;
    public: 
        affectation(variable * var, expr * expr);
        ~affectation();

        inline variable * get_var() const { return _var; }
        inline expr * get_expr() const { return _expr; }

        void visit(visitor & v) const;
    };
}

#endif