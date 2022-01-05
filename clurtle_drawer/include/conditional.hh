#ifndef CONDITIONAL_HH
#define CONDITIONAL_HH

#include "instr.hh"
#include "ope_bool.hh"


namespace clurtle {
    class conditional : public instr {
        ope_bool * _cond;
        instr * _cons;
        instr * _alt;

    public: 
        conditional(ope_bool * cond, instr * cons, instr * alt);
        ~conditional();

        inline ope_bool * get_cond() const { return _cond; }
        inline instr * get_cons() const { return _cons; }
        inline instr * get_alt() const { return _alt; }

        void visit(visitor & v) const;
    };
}

#endif