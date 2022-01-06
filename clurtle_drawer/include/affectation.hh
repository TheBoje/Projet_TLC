#ifndef AFFECTATION_HH
#define AFFECTATION_HH

#include <string>

#include "instr.hh"
#include "expr.hh"

namespace clurtle {
    class affectation : public instr {
        std::string _var;
        expr *      _expr;
    public: 
        affectation(std::string var, expr * expr);
        ~affectation();

        inline std::string get_var() const { return _var; }
        inline expr * get_expr() const { return _expr; }

        void visit(visitor & v) const;
    };
}

#endif