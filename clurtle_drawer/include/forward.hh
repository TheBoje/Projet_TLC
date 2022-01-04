#ifndef FORWARD_HH
#define FORWARD_HH

#include "instr.hh"

namespace clurtle {
    class forward : public instr {
        int _amount;
    public:
        forward(int amount);
        ~forward();

        inline int get_amount() const { return _amount; }

        void visit(visitor & v) const;
    };
}

#endif