#ifndef FORWARD_HH
#define FORWARD_HH

#include "instr.hh"
#include "expr.hh"

namespace clurtle {
    class forward : public instr {
        expr * _amount;
    public:
        forward(expr * amount);
        ~forward();

        inline expr * get_amount() const { return _amount; }

        void visit(visitor & v) const;
    };
}

#endif