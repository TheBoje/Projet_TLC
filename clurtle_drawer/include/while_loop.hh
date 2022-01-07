#ifndef WHILE_LOOP_HH
#define WHILE_LOOP_HH

#include "instr.hh"
#include "expr.hh"
#include "seq.hh"

namespace clurtle {
    class while_loop : public instr {
        expr * _cond;
        seq_item * _body;

    public:
        while_loop(expr * cond, seq_item * body);
        ~while_loop();

        inline expr * get_cond() const { return _cond; }
        inline seq_item * get_body() const { return _body; }

        void visit(visitor & v) const;
    };
}

#endif