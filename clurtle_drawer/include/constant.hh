#ifndef CONSTANT_HH
#define CONSTANT_HH

#include "expr.hh"

namespace clurtle {
    class constant : public expr {
        int _value;
    public:
        constant(int value);
        ~constant();

        inline int get_value() const { return _value; }
    
        void visit(visitor & v) const;
    };
}

#endif