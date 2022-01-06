#ifndef LINE_HH
#define LINE_HH

#include "instr.hh"
#include "expr.hh"

namespace clurtle {
    class line : public instr {
        expr * _length;
    public:
        line(expr * length);
        ~line();

        inline expr * get_length() const { return _length; }

        void visit(visitor & v) const;    
    };
}

#endif