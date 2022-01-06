#ifndef DOWN_HH
#define DOWN_HH

#include "instr.hh"

namespace clurtle {
    class down : public instr {
    public:
        void visit(visitor & v) const { return v.visit_down(this); }
    };
}

#endif