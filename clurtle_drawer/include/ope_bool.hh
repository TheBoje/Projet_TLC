#ifndef OPE_BOOL_HH
#define OPE_BOOL_HH

#include "expr.hh"

namespace clurtle {

    enum ope_bool_symbol {
        GT,
        GEQ,
        LT,
        LEQ,
        EQ,
        AND,
        OR
    };

    class ope_bool : public expr {
        expr * _left;
        ope_bool_symbol _symbol;
        expr * _right;

    public:
        ope_bool(ope_bool_symbol o, expr * left, expr * right);
        ~ope_bool();

        inline expr * get_left() const { return _left; }
        inline ope_bool_symbol get_symbol() const { return _symbol; } 
        inline expr * get_right() const { return _right; }

        void visit(visitor & v) const;
    };

}

#endif