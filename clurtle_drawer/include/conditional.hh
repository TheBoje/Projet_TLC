#ifndef CONDITIONAL_HH
#define CONDITIONAL_HH

#include "instr.hh"
#include "expr.hh"
#include "seq.hh"

namespace clurtle {
    class conditional : public instr {
        expr *  _cond;
        seq_item * _cons;
        seq_item * _alt;

    public: 
        conditional(expr * cond, seq_item * cons, seq_item * alt = nullptr);
        ~conditional();

        inline expr * get_cond() const { return _cond; }
        inline seq_item * get_cons() const { return _cons; }
        inline seq_item * get_alt() const { return _alt; }

        void visit(visitor & v) const;
    };
}

#endif