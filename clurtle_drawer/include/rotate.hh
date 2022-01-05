#ifndef ROTATE_HH
#define ROTATE_HH

#include "instr.hh"
#include "expr.hh"

namespace clurtle {
    class rotate : public instr {
            expr * _amount;
    public:
        rotate(expr * amount);
        ~rotate();

        inline expr * get_amount() const { return _amount; }

        void visit(visitor & v) const;
    };
}

#endif