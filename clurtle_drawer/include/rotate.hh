#ifndef ROTATE_HH
#define ROTATE_HH

#include "instr.hh"

namespace clurtle {
    class rotate : public instr {
            int _amount;
    public:
        rotate(int amount);
        ~rotate();

        inline int get_amount() const { return _amount; }

        void visit(visitor & v) const;
    };
}

#endif