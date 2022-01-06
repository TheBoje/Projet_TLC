#ifndef UP_HH
#define UP_HH

#include "instr.hh"

namespace clurtle {
    class up : public instr {
    public:
        void visit(visitor & v) const { return v.visit_up(this); }
    };
}

#endif