#ifndef CONDITIONAL_HH
#define CONDITIONAL_HH

#include "instr.hh"
#include "expr.hh"

namespace clurtle {
    class conditional : public instr {
        expr *  _cond;
        instr * _cons;
        instr * _alt;

    public: 
        conditional(expr * cond, instr * cons, instr * alt);
        ~conditional();

        inline expr * get_cond() const { return _cond; }
        inline instr * get_cons() const { return _cons; }
        inline instr * get_alt() const { return _alt; }

        void visit(visitor & v) const;
    };
}

#endif