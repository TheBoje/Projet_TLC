#ifndef WHILE_LOOP_HH
#define WHILE_LOOP_HH

#include "instr.hh"
#include "expr.hh"

namespace clurtle {
    class while_loop : public instr {
        expr * _cond;
        instr * _body;

    public:
        while_loop(expr * cond, instr * body);
        ~while_loop();

        inline expr * get_cond() const { return _cond; }
        inline instr * get_body() const { return _body; }

        void visit(visitor & v) const;
    };
}

#endif