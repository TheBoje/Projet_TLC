#ifndef COLOR_H
#define COLOR_H

#include "expr.hh"
#include <array>

namespace clurtle {
    class color : public expr {
        expr * _r; 
        expr * _g; 
        expr * _b; 
    public: 
        color(expr * r, expr * g, expr * b);
        ~color();

        inline expr * get_r() const { return _r; }
        inline expr * get_g() const { return _g; }
        inline expr * get_b() const { return _b; }

        void visit(visitor & v) const;
    };
}

#endif