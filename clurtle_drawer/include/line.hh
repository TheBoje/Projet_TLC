#ifndef LINE_HH
#define LINE_HH

#include "instr.hh"

namespace clurtle {
    class line : public instr {
        int _length;
    public:
        line(int length);
        ~line();

        inline int get_length() const { return _length; }

        void visit(visitor & v) const;    
    };
}

#endif