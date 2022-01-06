#ifndef RECTANGLE_HH
#define RECTANGLE_HH

#include "instr.hh"
#include "expr.hh"

namespace clurtle {
    class rectangle : public instr {
        expr * _length;
        expr * _width;
    public:
        rectangle(expr * length, expr * width);
        ~rectangle();

        inline expr * get_length() const { return _length; }
        inline expr * get_width() const { return _width; }

        void visit(visitor & v) const;    
    
    };
}

#endif